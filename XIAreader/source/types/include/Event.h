/*******************************************************************************
 * Copyright (C) 2016-2018 Vetle W. Ingeberg                                   *
 * Author: Vetle Wegner Ingeberg, v.w.ingeberg@fys.uio.no                      *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * This program is free software; you can redistribute it and/or modify it     *
 * under the terms of the GNU General Public License as published by the       *
 * Free Software Foundation; either version 3 of the license, or (at your      *
 * option) any later version.                                                  *
 *                                                                             *
 * This program is distributed in the hope that it will be useful, but         *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General   *
 * Public License for more details.                                            *
 *                                                                             *
 * You should have recived a copy of the GNU General Public License along with *
 * the program. If not, see <http://www.gnu.org/licenses/>.                    *
 *                                                                             *
 *******************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <memory>

#include <cstdint>

#include "experimentsetup.h"
#include "TDRWordBuffer.h"
#include "XIA_CFD.h"

//! Structure type to contain individual decoded events.
//! \author Vetle W. Ingeberg
//! \date 2015-2018
//! \copyright GNU Public License v. 3
/*typedef struct subevt_t {
	uint16_t address;		//!< Holds the address of the ADC. 
    uint16_t adcdata;		//!< Data read out from the ADC.
    uint16_t cfddata;       //!< Fractional difference of before/after zero-crossing.
    double cfdcorr;         //!< Correction from the CFD.
    int64_t timestamp;		//!< Timestamp in [ns].
    char cfdfail;           //!< Flag to tell if the CFD was forced or not.

    subevt_t() : address( 0 ), adcdata( 0 ), cfddata( 0 ), cfdcorr( 0 ), timestamp( 0 ), cfdfail( 0 ) { }

    subevt_t(const word_t &w);

} subevent_t;*/

typedef word_t subevent_t;


//! Object to contain built events.
//! \author Vetle W. Ingeberg
//! \date 2017-2018
//! \copyright GNU Public License v. 3
struct Event {

    subevent_t w_labr[NUM_LABR_DETECTORS][MAX_WORDS_PER_DET];   //!< Array to contain LaBr words
    int n_labr[NUM_LABR_DETECTORS];                         //!< Number of LaBr words populated
    int tot_labr;                                           //!< Total number of LaBr words in the event

    subevent_t w_dEdet[NUM_SI_DE_DET][MAX_WORDS_PER_DET];       //!< Array to contain Si words from the dE rings
    int n_dEdet[NUM_SI_DE_DET];                            //!< Number of Si words populated from the dE rings
    int tot_dEdet;                                          //!< Total number of Si words from the dE rings

    subevent_t w_Edet[NUM_SI_E_DET][MAX_WORDS_PER_DET];         //!< Array to contain Si words from the dE sectors
    int n_Edet[NUM_SI_E_DET];                               //!< Number of Si words populated from the dE sectors
    int tot_Edet;                                           //!< Total number of Si words from the dE sectors

    subevent_t w_Eguard[NUM_SI_E_GUARD][MAX_WORDS_PER_DET];    //!< Array to contain Si words from the E sectors
    int n_Eguard[NUM_SI_E_GUARD];                          //!< Number of Si words populated from the E sectors
    int tot_Eguard;                                         //!< Total number of Si words from the dE sectors

    subevent_t w_ppac[NUM_PPAC][MAX_WORDS_PER_DET];         //!< Array to contain PPAC words from the PPACs
    int n_ppac[NUM_PPAC];                                   //!< Number of PPAC words for each PPAC in the event
    int tot_ppac;

    subevent_t w_RFpulse[MAX_WORDS_PER_DET];                    //!< Array to contain RF pulse words
    int n_RFpulse;                                          //!< Number of RF pulses populated

    int length;  //! Total length of the event (in no. of words)


    //! Constructor
    Event() { Reset(); }

    //! Destructor
    ~Event(){ Reset(); }

    //! Set all counters to zero
    void Reset()
    {
        int i;

        // Clearing all LaBr counters
        tot_labr = 0;
        for (size_t i = 0 ; i < NUM_LABR_DETECTORS ; ++i) {
            n_labr[i] = 0;
        }

        // Clearing dE sections
        tot_dEdet = 0;
        for (i = 0 ; i < NUM_SI_DE_DET ; ++i)
            n_dEdet[i] = 0;

        // Clearing E detectors
        tot_Edet = 0;
        for (i = 0 ; i < NUM_SI_E_DET ; ++i)
            n_Edet[i] = 0;

        // Clearing E guard rings
        tot_Eguard = 0;
        for (i = 0 ; i < NUM_SI_E_GUARD ; ++i)
            n_Eguard[i] = 0;

        // Clearing ppac
        tot_ppac = 0;
        for (i = 0 ; i < NUM_PPAC ; ++i)
            n_ppac[i] = 0;

        // Clearing RF pulses
        n_RFpulse = 0;

        // Resetting event length.
        length = 0;
    }

};



#endif // EVENT_H
