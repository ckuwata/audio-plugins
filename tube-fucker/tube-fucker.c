#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define PLUGIN_URI "http://return0.info/plugins/tube-fucker"

typedef enum {
    PEDAL_GAIN   = 0,
    PEDAL_VOL    = 1,
    PEDAL_INPUT  = 2,
    PEDAL_OUTPUT = 3
} Ports;

typedef struct {
    const float* gain;
    const float* volume;
    const float* input;
    float* output;
} TubeFucker ;

float apply(const TubeFucker* pedal, const float a);

static LV2_Handle instantiate(
    const LV2_Descriptor*     descriptor,
    double                    rate,
    const char*               bundle_path,
    const LV2_Feature* const* features) {
    TubeFucker* instance = (TubeFucker*)malloc(sizeof(TubeFucker));
    return instance;
}

static void connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
    TubeFucker* pedal = (TubeFucker*)instance;
    switch ((Ports)port) {
    case PEDAL_GAIN:
            pedal->gain = (const float*)data;
            break;
    case PEDAL_VOL:
            pedal->volume = (const float*)data;
            break;
    case PEDAL_INPUT:
            pedal->input = (const float*)data;
            break;
    case PEDAL_OUTPUT:
            pedal->output = (float*)data;
            break;
    }
}

static void activate(LV2_Handle instance)
{
}

static void run(LV2_Handle instance, uint32_t n_samples)
{
    const TubeFucker* pedal = (const TubeFucker*)instance;
    const float* const input  = pedal->input;
    float* const       output = pedal->output;

    for (uint32_t pos = 0; pos < n_samples; pos++) {
        output[pos] = apply(pedal, input[pos]);
    }
}

static void deactivate(LV2_Handle instance) {
}

static void cleanup(LV2_Handle instance) {
    free(instance);
}

static const void* extension_data(const char* uri)
{
    return NULL;
}

static const LV2_Descriptor descriptor = {
        PLUGIN_URI,
        instantiate,
        connect_port,
        activate,
        run,
        deactivate,
        cleanup,
        extension_data
};

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
        switch (index) {
        case 0:  return &descriptor;
        default: return NULL;
        }
}

float apply(const TubeFucker* pedal, const float a) {
    float d = (a + powf(a, 3)) * powf(40.0f, (*pedal->gain) * 0.05f) * 10.0f;
    if (d > 1) {
        d = 2.0f/3.0f;
    } else if (d < -1) {
        d = -2.0f/3.0f;
    } else {
        d = d - powf(d, 3)/ 3;
    }
    d = d / 10.0f;
    return d * powf(10.0f, (*(pedal->volume)) * 0.05f);
}

