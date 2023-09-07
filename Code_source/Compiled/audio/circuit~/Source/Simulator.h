//
//  CircuitSimulator.hpp
//  pd-circuit
//
//  Created by Timothy Schoen on 05/09/2023.
//
#include "m_pd.h"

#pragma once

#ifdef __cplusplus

enum ComponentType
{
    tResistor,
    tCapacitor,
    tVoltage,
    tDiode,
    tBJT,
    tTransformer,
    tGyrator,
    tInductor,
    tOpAmp,
    tPotmeter,
    tProbe
};

extern "C"
{
#endif

void* simulator_create(int argc, t_atom* argv, double sampleRate);
void simulator_free(void* netlist);

void simulator_set_input(void* netlist, int idx, double input);
double simulator_get_output(void* netlist, int idx);
void simulator_tick(void* net);

int simulator_num_inlets(void* net);
int simulator_num_outlets(void* netlist);

void* simulator_reset(void* netlist, double sampleRate);
void simulator_set_dc_block(void* netlist, int block);
void simulator_set_iter(void* netlist, int iter);

#ifdef __cplusplus
}
#endif
