/* -*- c++ -*- */
/*
 * Copyright 2018 Johannes Demel.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_GFDM_TRANSMITTER_KERNEL_H
#define INCLUDED_GFDM_TRANSMITTER_KERNEL_H

#include <gfdm/api.h>
#include "gfdm_kernel_utils.h"
#include <gfdm/resource_mapper_kernel_cc.h>
#include <gfdm/modulator_kernel_cc.h>
#include <gfdm/add_cyclic_prefix_cc.h>

namespace gr {
  namespace gfdm {

    /*!
     * \brief <+description+>
     *
     */
    class GFDM_API transmitter_kernel
    {
    public:
      typedef gr::gfdm::gfdm_kernel_utils::gfdm_complex gfdm_complex;
      typedef boost::shared_ptr<transmitter_kernel> sptr;

      transmitter_kernel(int timeslots, int subcarriers, int active_subcarriers,
                         int cp_len, int cs_len, int ramp_len,
                         std::vector<int> subcarrier_map, bool per_timeslot,
                         int overlap, std::vector<gfdm_complex> frequency_taps,
                         std::vector<gfdm_complex> window_taps,
                         std::vector<gfdm_complex> preamble);
      ~transmitter_kernel();

      int input_vector_size() {return d_mapper->input_vector_size();}
      int output_vector_size() {return d_prefixer->frame_size() + d_preamble.size();}
      void generic_work(gfdm_complex* p_out, const gfdm_complex* p_in, const int ninput_size);

    private:
      resource_mapper_kernel_cc::sptr d_mapper;
      modulator_kernel_cc::sptr d_modulator;
      add_cyclic_prefix_cc::sptr d_prefixer;

      gfdm_complex* d_mapped;
      gfdm_complex* d_frame;
      std::vector<gfdm_complex> d_preamble;
    };

  } // namespace gfdm
} // namespace gr

#endif /* INCLUDED_GFDM_TRANSMITTER_KERNEL_H */

