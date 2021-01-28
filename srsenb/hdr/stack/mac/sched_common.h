/**
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef SRSLTE_SCHED_COMMON_H
#define SRSLTE_SCHED_COMMON_H

#include "srslte/adt/bounded_bitset.h"
#include "srslte/common/tti_point.h"
#include "srslte/interfaces/sched_interface.h"

namespace srsenb {

/***********************
 *     Constants
 **********************/

constexpr float tti_duration_ms = 1;

/***********************
 *   Helper Types
 **********************/

//! Struct used to store possible CCE locations.
struct sched_dci_cce_t {
  uint32_t cce_start[4][6]; ///< Stores starting CCE for each aggr level index and CCE location index
  uint32_t nof_loc[4];      ///< Number of possible CCE locations for each aggregation level index
};

/// structs to bundle together all the sched arguments, and share them with all the sched sub-components
class sched_cell_params_t
{
  struct regs_deleter {
    void operator()(srslte_regs_t* p);
  };

public:
  bool set_cfg(uint32_t                             enb_cc_idx_,
               const sched_interface::cell_cfg_t&   cfg_,
               const sched_interface::sched_args_t& sched_args);
  // convenience getters
  uint32_t nof_prbs_to_rbgs(uint32_t nof_prbs) const { return srslte::ceil_div(nof_prbs, P); }
  uint32_t nof_prb() const { return cfg.cell.nof_prb; }
  uint32_t get_dl_lb_nof_re(tti_point tti_tx_dl, uint32_t nof_prbs_alloc) const;
  uint32_t get_dl_nof_res(srslte::tti_point tti_tx_dl, const srslte_dci_dl_t& dci, uint32_t cfi) const;

  uint32_t                                       enb_cc_idx = 0;
  sched_interface::cell_cfg_t                    cfg        = {};
  const sched_interface::sched_args_t*           sched_cfg  = nullptr;
  std::unique_ptr<srslte_regs_t, regs_deleter>   regs;
  std::array<sched_dci_cce_t, 3>                 common_locations = {};
  std::array<std::array<sched_dci_cce_t, 10>, 3> rar_locations    = {};
  std::array<uint32_t, 3>                        nof_cce_table    = {}; ///< map cfix -> nof cces in PDCCH
  uint32_t                                       P                = 0;
  uint32_t                                       nof_rbgs         = 0;

  using dl_nof_re_table = srslte::bounded_vector<
      std::array<std::array<std::array<uint32_t, SRSLTE_NOF_CFI>, SRSLTE_NOF_SLOTS_PER_SF>, SRSLTE_NOF_SF_X_FRAME>,
      SRSLTE_MAX_PRB>;
  using dl_lb_nof_re_table = std::array<srslte::bounded_vector<uint32_t, SRSLTE_MAX_PRB>, SRSLTE_NOF_SF_X_FRAME>;

  /// Table of nof REs
  dl_nof_re_table nof_re_table;
  /// Cached computation of Lower bound of nof REs
  dl_lb_nof_re_table nof_re_lb_table;
};

using ue_cce_locations_table = std::array<std::array<sched_dci_cce_t, SRSLTE_NOF_SF_X_FRAME>, SRSLTE_NOF_CFI>;

//! Bitmask used for CCE allocations
using pdcch_mask_t = srslte::bounded_bitset<sched_interface::max_cce, true>;

//! Bitmask that stores the allocared DL RBGs
using rbgmask_t = srslte::bounded_bitset<25, true>;

//! Bitmask that stores the allocated UL PRBs
using prbmask_t = srslte::bounded_bitset<100, true>;

//! Struct to express a {min,...,max} range of RBGs
struct prb_interval;
struct rbg_interval : public srslte::interval<uint32_t> {
  using interval::interval;
  static rbg_interval rbgmask_to_rbgs(const rbgmask_t& mask);
};

//! Struct to express a {min,...,max} range of PRBs
struct prb_interval : public srslte::interval<uint32_t> {
  using interval::interval;

  static prb_interval rbgs_to_prbs(const rbg_interval& rbgs, uint32_t cell_nof_prb);
  static prb_interval riv_to_prbs(uint32_t riv, uint32_t nof_prbs, int nof_vrbs = -1);
};

} // namespace srsenb

#endif // SRSLTE_SCHED_COMMON_H