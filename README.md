# HitMarker SA-MP

A hitmarker is the little x that pops up in your crosshairs when one of your bullets hits someone.

![Crosshair](https://user-images.githubusercontent.com/56031386/215626770-c26d8596-7b2f-4647-a064-b6ddd4d63fdc.png)


## Installation

Include in your code and begin using the library:
```pawn
#include <Hitmarker>
```
## Documentation
Documentation can be found on the [Wiki](https://github.com/Bren828/HitMarker-SA-MP/wiki).

## Example

```pawn
CMD:Hitmarker(playerid)
{
    if(HitmarkerStatus(playerid) == false) // Узнаем состояние хитмаркера
    {
        // Включаем хитмаркер
        HitmarkerEnabled(playerid);

        // Setting the hit colors
        HitmarkerColor(playerid, HITMARKER_BODYPART_TORSO, 0xFFFFFFFF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_GROIN, 0x7CFC00FF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_LEFT_ARM, 0xFFA500FF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_RIGHT_ARM, 0xFFD700FF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_LEFT_LEG, 0x00BFFFFF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_RIGHT_LEG, 0x00FFFFFF);
        HitmarkerColor(playerid, HITMARKER_BODYPART_HEAD, 0xFF00FFFF);

        HitmarkerColor(playerid, HITMARKER_KILLSHOTS, 0xFF0000FF);
        HitmarkerColor(playerid, HITMARKER_VEHICLE_DAMAGE, 0xB03060FF);

        // Включаем индикацию урона по транспорту
        HitmarkerEnableVehicleDamage(playerid, true);

        // Отключаем индикацию урона оружием (ID: 5) - Бейсбольная бита
        HitmarkerDisableWeapon(playerid, WEAPON_BAT, true);

        // Отключаем индикацию урона наносимого воздушным транспортом при помощи пулемета
        HitmarkerDisableWeapon(playerid, HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN, true);

        GameTextForPlayer(playerid, "Hitmarker ~g~~h~On", 1200, 4);
    }
    else 
    {
        // Выключаем хитмаркер
        HitmarkerDisable(playerid);
        GameTextForPlayer(playerid, "Hitmarker ~r~~h~Off", 1200, 4);
    }
    return 1;
}
```
