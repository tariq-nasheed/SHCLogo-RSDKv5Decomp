#include "../GameAPI/C/GameAPI/Game.h"
#include "ModConfig.h"
#include "LogoSetup.h"
#include "SHCLogo.h"

#if RETRO_USE_MOD_LOADER
#if RETRO_REV02
  #define SHCLOGO_PRINT(mode, ...) RSDK.PrintLog(mode, "[SHCLogo] "__VA_ARGS__);
#else
  #define SHCLOGO_PRINT(mode, ...) { \
    char str[512]; \
    sprintf(str, "[SHCLOGO] "__VA_ARGS__); \
    RSDK.PrintMessage(str, MESSAGE_STRING); \
  }
#endif

#define IMPORT_PUBLIC_FUNC(name) { \
  name = Mod.GetPublicFunction(NULL, #name); \
  if (name == NULL) SHCLOGO_PRINT(PRINT_ERROR, #name" is not a public function\n"); \
}
#define HOOK_STATE(name, priority) { \
  void (*name##_fn) = Mod.GetPublicFunction(NULL, #name); \
  if (name##_fn == NULL) SHCLOGO_PRINT(PRINT_ERROR, #name" is not a public function\n") \
  else Mod.RegisterStateHook(name##_fn, name##_HOOK, priority); \
}
#define HOOK_IMPORTED_STATE(name, priority) Mod.RegisterStateHook(name, name##_HOOK, priority)

DLLExport bool32 LinkModLogic(EngineInfo* info, const char* id);
#endif //! RETRO_USE_MOD_LOADER

ModConfig_t ModConfig;

void InitModAPI() {
	ModConfig.skipSHCLogo = Mod.GetSettingsBool("", "Config:skipSHCLogo", false);
	Mod.SetSettingsBool("Config:skipSHCLogo", ModConfig.skipSHCLogo);

	RSDK_REGISTER_OBJECT(SHCLogo);
	MOD_REGISTER_OBJECT_HOOK(LogoSetup);
	IMPORT_PUBLIC_FUNC(LogoSetup_State_NextLogos);
	IMPORT_PUBLIC_FUNC(LogoSetup_State_ShowLogos);
	IMPORT_PUBLIC_FUNC(LogoSetup_Draw_Fade);
	HOOK_STATE(LogoSetup_State_FadeToNextLogos, true);
	HOOK_IMPORTED_STATE(LogoSetup_State_ShowLogos, true);
	HOOK_IMPORTED_STATE(LogoSetup_State_NextLogos, true);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI();

bool32 LinkModLogic(EngineInfo* info, const char* id) {
#if MANIA_USE_PLUS
	LinkGameLogicDLL(info);
#else
	LinkGameLogicDLL(*info);
#endif
	globals = Mod.GetGlobals();
	modID = id;
	InitModAPI();
	return true;
}
#endif //! RETRO_USE_MOD_LOADER