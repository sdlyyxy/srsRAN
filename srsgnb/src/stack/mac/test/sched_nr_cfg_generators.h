/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifndef SRSRAN_SCHED_NR_CFG_GENERATORS_H
#define SRSRAN_SCHED_NR_CFG_GENERATORS_H

#include "srsgnb/hdr/stack/mac/sched_nr_interface.h"
#include "srsran/common/phy_cfg_nr_default.h"

namespace srsenb {

inline srsran_coreset_t get_default_coreset0(uint32_t nof_prb)
{
  srsran_coreset_t coreset{};
  coreset.id                   = 0;
  coreset.duration             = 1;
  coreset.precoder_granularity = srsran_coreset_precoder_granularity_reg_bundle;
  for (uint32_t i = 0; i < SRSRAN_CORESET_FREQ_DOMAIN_RES_SIZE; ++i) {
    coreset.freq_resources[i] = i < (nof_prb / 6);
  }
  return coreset;
}

inline sched_nr_interface::cell_cfg_t get_default_cell_cfg(
    const srsran::phy_cfg_nr_t& phy_cfg = srsran::phy_cfg_nr_default_t{srsran::phy_cfg_nr_default_t::reference_cfg_t{}})
{
  sched_nr_interface::cell_cfg_t cell_cfg{};

  cell_cfg.carrier = phy_cfg.carrier;
  cell_cfg.duplex  = phy_cfg.duplex;
  cell_cfg.ssb     = phy_cfg.ssb;

  cell_cfg.bwps.resize(1);
  cell_cfg.bwps[0].pdcch    = phy_cfg.pdcch;
  cell_cfg.bwps[0].pdsch    = phy_cfg.pdsch;
  cell_cfg.bwps[0].pusch    = phy_cfg.pusch;
  cell_cfg.bwps[0].rb_width = phy_cfg.carrier.nof_prb;

  return cell_cfg;
}

inline std::vector<sched_nr_interface::cell_cfg_t> get_default_cells_cfg(
    uint32_t                    nof_sectors,
    const srsran::phy_cfg_nr_t& phy_cfg = srsran::phy_cfg_nr_default_t{srsran::phy_cfg_nr_default_t::reference_cfg_t{}})
{
  std::vector<sched_nr_interface::cell_cfg_t> cells;
  cells.reserve(nof_sectors);
  for (uint32_t i = 0; i < nof_sectors; ++i) {
    cells.push_back(get_default_cell_cfg(phy_cfg));
  }
  return cells;
}

inline sched_nr_interface::ue_cfg_t get_rach_ue_cfg(uint32_t cc)
{
  sched_nr_interface::ue_cfg_t uecfg{};

  // set Pcell
  uecfg.carriers.resize(1);
  uecfg.carriers[0].active = true;
  uecfg.carriers[0].cc     = cc;

  // set SRB0 as active
  uecfg.ue_bearers[0].direction = mac_lc_ch_cfg_t::BOTH;

  // set basic PHY config
  uecfg.phy_cfg     = srsran::phy_cfg_nr_default_t{srsran::phy_cfg_nr_default_t::reference_cfg_t{}};
  uecfg.phy_cfg.csi = {};

  return uecfg;
}

inline sched_nr_interface::ue_cfg_t get_default_ue_cfg(
    uint32_t                    nof_cc,
    const srsran::phy_cfg_nr_t& phy_cfg = srsran::phy_cfg_nr_default_t{srsran::phy_cfg_nr_default_t::reference_cfg_t{}})
{
  sched_nr_interface::ue_cfg_t uecfg{};
  uecfg.carriers.resize(nof_cc);
  for (uint32_t cc = 0; cc < nof_cc; ++cc) {
    uecfg.carriers[cc].cc     = cc;
    uecfg.carriers[cc].active = true;
  }
  uecfg.phy_cfg                 = phy_cfg;
  uecfg.ue_bearers[0].direction = mac_lc_ch_cfg_t::BOTH;

  return uecfg;
}

} // namespace srsenb

#endif // SRSRAN_SCHED_NR_CFG_GENERATORS_H
