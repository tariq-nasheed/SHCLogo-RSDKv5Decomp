#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
	bool32 skipSHCLogo;
} ModConfig_t;

extern ModConfig_t ModConfig;

#endif //! MOD_CONFIG_H