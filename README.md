SHC Mania splash screen ported to the RSDKv5 decomp via GameAPI

# Usage
integrate in your own mod manually by copying over source files or compile it and use the
logic file in your `mod.ini` like so:

```
Name          = ExampleMod
Description   = ???
Author        = me :)
Version       = 1.0.0
TargetVersion = 5
LogicFile     = SHCLogo,ExampleMod

```
ALSO you can skip the splash screen by setting `skipSHCLogo` to Y in `modSettings.ini`
# Original Authors
- Graphics by MarkeyJester and mrcat-pixel (based on logo by Cinossu)
- Implementation by SuperSonic16, LJSTAR, and rubberduckycooly
- Coding based on SAGE splash screen object by TheStoneBanana
