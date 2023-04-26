# HitMarker SA-MP

A hitmarker is the little x that pops up in your crosshairs when one of your bullets hits someone.

![Crosshair](https://i.imgur.com/8O2xrWn.png)

## Main features
* Изменение цвета хитмаркера при попадании в разные части тела игрока, транспорта, и при полном убийстве игрока.
* Отключение хитмаркера для всех видов оружия, включая спец оружие воздушного транспорта.
* Установка определенного звука при попадании.
* Настройка положение и размера хитмаркера.
* Включение/Выключение индикации попадания по игроку и по транспорту.

## Reference
* [Download](https://github.com/Bren828/HitMarker-SA-MP#download)
* [Installation](https://github.com/Bren828/HitMarker-SA-MP#installation)
* [Example](https://github.com/Bren828/HitMarker-SA-MP#example)
* [Functions](https://github.com/Bren828/HitMarker-SA-MP#functions)
* [Definition](https://github.com/Bren828/HitMarker-SA-MP#definition)
  * [Editing Color change](https://github.com/Bren828/HitMarker-SA-MP#editing-color-change)
  * [Editing Disabling weapons](https://github.com/Bren828/HitMarker-SA-MP#editing-disabling-weapons)
  * [Change position](https://github.com/Bren828/HitMarker-SA-MP#change-position)

## Download
[Releases page](https://github.com/Bren828/HitMarker-SA-MP/releases)

## Installation

Include in your code and begin using the library:
```pawn
#include <hitmarker>
```

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

## Functions

#### HitmarkerEnabled(playerid)
> Enable hitmarker
> * `playerid` - The ID of the player

#### HitmarkerDisable(playerid)
> Disable hitmarker
> * `playerid` - The ID of the player
  
#### bool:HitmarkerStatus(playerid)
> Check hitmarker status
> * `playerid` - The ID of the player
> * Return (true) if enabled or (false) if disabled
  
#### HitmarkerColor(playerid, type, color)
> Change hitmarker color
> * `playerid` - The ID of the player
> * `type` - [Color definition](https://github.com/Bren828/HitMarker-SA-MP/wiki/Color-change)
> * `color` - The color to set. Supports alpha values.

#### GetHitmarkerColor(playerid, type)
> Узнать текущий цвет хитмаркера
> * `playerid` - The ID of the player
> * `type` - [Color definition](https://github.com/Bren828/HitMarker-SA-MP/wiki/Color-change)
> * Returns the color

#### HitmarkerDisableWeapon(playerid, weaponid, bool:disable)
> Выключить хитмаркер для определенного оружия
> * `playerid` - The ID of the player
> * `weaponid` - [Weapon IDs](https://github.com/Bren828/HitMarker-SA-MP/wiki/disabling-weapons)
> * `disable` - `true` to disable / `false` to enable
> * **При отключении огневого оружия, отключается оружие (ID: 18, 37)**
> * **При отключении взрывного оружия, отключается оружие (ID: 16, 35, 36, 39, 51) Не распространяется на воздушный транспорт.**

#### GetHitmarkerDisabledWeapon(playerid, weaponid)
> Узнать статус хитмаркера у определенного оружия
> * `playerid` - The ID of the player
> * `weaponid` - [Weapon IDs](https://github.com/Bren828/HitMarker-SA-MP/wiki/disabling-weapons)
> * Return (true) if disabled or (false) if enabled

#### HitmarkerSoundDamage(playerid, soundid)
> Включить звук попадания
> * `playerid` - The ID of the player
> * `soundid` - Sound IDs

#### GetHitmarkerSoundDamage(playerid)
> Узнать текущий звук попадания
> * `playerid` - The ID of the player
> * Returns sound ID

#### HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y)
> Изменить положение хитмаркера 
> * `playerid` - The ID of the player
> * `crosshair_type` - [Position determination](https://github.com/Bren828/HitMarker-SA-MP/wiki/Change-position)
> * `Float:x` - The X (left/right) coordinate to create the textdraw at.
> * `Float:y` - The Y (up/down) coordinate to create the textdraw at.
> * `Float:size_x` - Width
> * `Float:size_y` - Height 

#### GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:size_x, &Float:size_y)
> Узнать текущие положение хитмаркера
> * `playerid` - The ID of the player
> * `crosshair_type` - [Position determination](https://github.com/Bren828/HitMarker-SA-MP/wiki/Change-position)
> * `&Float:x` - The X (left/right) coordinate
> * `&Float:y` - The Y (up/down) coordinate
> * `&Float:size_x` - Width
> * `&Float:size_y` - Height 

#### HitmarkerEnablePlayerDamage(playerid, bool:enable)
> Включить индикацию урона по игроку
> * `playerid` - The ID of the player
> * `enable` - `true` to enable / `false` to disable
> * По стандарту включено

#### GetHitmarkerEnablePlayerDamage(playerid)
> Узнать статус индикации урона по игроку
> * `playerid` - The ID of the player
> * Return (true) if enabled or (false) if disabled

#### HitmarkerEnableVehicleDamage(playerid, bool:enable)
> Включить индикацию урона по транспорту
> * `playerid` - The ID of the player
> * `enable` - `true` to enable / `false` to disable

#### GetHitmarkerEnableVehicleDamage(playerid)
> Узнать статус индикации урона по транспорту
> * `playerid` - The ID of the player
> * Return (true) if enabled or (false) if disabled


## Definition

#### Editing Color change

| Definition    | ID | Notes |
| --------------|:--:|-------|
| HITMARKER_KILLSHOTS | 0 | При полном убийстве игрока |
| HITMARKER_VEHICLE_DAMAGE | 1 | При попадании по транспорту |  
| HITMARKER_BODYPART_TORSO | 3 | При попадании по торсу |
| HITMARKER_BODYPART_GROIN | 4  | При попадании по паху |
| HITMARKER_BODYPART_LEFT_ARM | 5 | При попадании по левой руке |
| HITMARKER_BODYPART_RIGHT_ARM | 6 | При попадании по правой руке |
| HITMARKER_BODYPART_LEFT_LEG | 7 | При попадании по левой ноге |
| HITMARKER_BODYPART_RIGHT_LEG | 8 | При попадании по правой ноге |
| HITMARKER_BODYPART_HEAD | 9 | При попадании в голову |

#### Usage
```pawn
HitmarkerColor(playerid, HITMARKER_BODYPART_TORSO, 0xFFFFFFFF);
```

---

#### Editing Disabling weapons
###### Дополнительные определения для хитмаркера

| Icon |Definition            | ID  | Notes | 
-------|-----------------|-----|-------|
| ![](https://assets.open.mp/assets/images/deathIcons/death-fist.gif) | HITMARKER_WEAPON_FIST | 0   | Урон получен кулаком |
| ![](https://assets.open.mp/assets/images/deathIcons/death-heliBlades.gif) | HITMARKER_DEATH_UNDER_VEHICLE | 50 | Игрок умер под транспортом или от винтов вертолета |
| ![](https://assets.open.mp/assets/images/deathIcons/death-explosion.gif) | HITMARKER_ALL_EXPLOSION | 51 | Игрок умер от взрыва |
| ![](https://assets.open.mp/assets/images/deathIcons/death-m4.gif) | HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN | 52 | Игрок умер от спец оружие воздушного транспорта пулемет |
| ![](https://assets.open.mp/assets/images/deathIcons/death-explosion.gif) | HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS | 53 | Игрок умер от спец оружие воздушного транспорта ракета |

#### Usage
```pawn
HitmarkerDisableWeapon(playerid, HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN, true);
```

---

#### Change position

| Definition    | ID | Notes |
| --------------|:--:|-------|
| HITMARKER_STANDARD_CROSSHAIR | 0 | Изменение положение стандартного прицела<br />**Используется для огнестрельного оружия (ID: 22 - 33, 37 - 38)** |
| HITMARKER_CENTRE_CROSSHAIR | 1 | Изменение положение прицела по центру<br />**Используется для холодного оружия включая транспорт и при попадании в голову** | 

#### Usage
```pawn
HitmarkerPosition(playerid, HITMARKER_STANDARD_CROSSHAIR, 332.5, 172.5, 0.33, 0.7);
