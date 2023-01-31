# HitMarker SA-MP

A hitmarker is the little x that pops up in your crosshairs when one of your bullets hits someone.

![Crosshair](https://user-images.githubusercontent.com/56031386/215626770-c26d8596-7b2f-4647-a064-b6ddd4d63fdc.png)


## Installation

Include in your code and begin using the library:
```pawn
#include <Hitmarker>
```

## Definition

#### Color change
* `HITMARKER_KILLSHOTS`	
  * При полном убийстве игрока
* `HITMARKER_VEHICLE_DAMAGE`
  * При попадании по транспорту
* `HITMARKER_BODYPART_TORSO`
  * При попадании по торсу
* `HITMARKER_BODYPART_GROIN`
  * При попадании по паху
* `HITMARKER_BODYPART_LEFT_ARM`
  * При попадании по левой руке
* `HITMARKER_BODYPART_RIGHT_ARM`
  * При попадании по правой руке
* `HITMARKER_BODYPART_LEFT_LEG`
  * При попадании по левой ноге
* `HITMARKER_BODYPART_RIGHT_LEG`
  * При попадании по правой ноге
* `HITMARKER_BODYPART_HEAD`
  * При попадании в голову
  
#### Disabling weapons
* `HITMARKER_WEAPON_FIST`
  * Урон получен кулаком
* `HITMARKER_DEATH_UNDER_VEHICLE`
  * Игрок умер под транспортом или от винтов вертолета
* `HITMARKER_ALL_EXPLOSION`
  * Игрок умер от взрыва
* `HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN`
  * Игрок умер от спец оружие воздушного транспорта пулемет
* `HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS`
  * Игрок умер от спец оружие воздушного транспорта ракета

#### Change position
* `HITMARKER_STANDARD_CROSSHAIR`
  * Изменение положение стандартного прицела
  * Используется для огнестрельного оружия (ID: 22 - 33, 37 - 38)
* `HITMARKER_CENTRE_CROSSHAIR`
  * Изменение положение прицела по центру
  * Используется для холодного оружия включая транспорт
  
  
## Functions:

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
> * `type` - [Color change](https://github.com/Bren828/HitMarker-SA-MP/blob/main/README.md#definition)
> * `color` - 

#### GetHitmarkerColor(playerid, type)
> Узнать текущий цвет хитмаркера
> * `playerid` - The ID of the player
> * `type` - [Color change](https://github.com/Bren828/HitMarker-SA-MP/blob/main/README.md#definition)
> * Returns the color

#### HitmarkerDisableWeapon(playerid, weaponid, bool:disable)
> Выключить хитмаркер для определенного оружия
> * `playerid` - The ID of the player
> * `weaponid` - [Weapon IDs](https://github.com)
> * `disable` - `true` to enable / `false` to disable
> * При отключении огневого оружия, отключается оружие (ID: 18, 37)
> * При отключении взрывного оружия, отключается оружие (ID: 16, 35, 36, 39, 51) Не распространяется на воздушный транспорт.

#### GetHitmarkerDisabledWeapon(playerid, weaponid)
> Узнать статус хитмаркера у определенного оружия
> * `playerid` - The ID of the player
> * `weaponid` - [Weapon IDs](https://github.com)
> * Return (true) if enabled or (false) if disabled

#### HitmarkerSoundDamage(playerid, soundid)
> Включить звук попадания
> * `playerid` - The ID of the player
> * `soundid` - [Sound IDs](https://github.com/openmultiplayer/web/blob/master/docs/scripting/resources/sound-ids.md)

#### GetHitmarkerSoundDamage(playerid)
> Узнать текущий звук попадания
> * `playerid` - The ID of the player
> * Returns sound ID

#### HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y)
> Изменить положение хитмаркера 
> * `playerid` - [Change position](https://github.com/Bren828/HitMarker-SA-MP#change-position)
> * `crosshair_type` - 
> * `Float:x` - 
> * `Float:y` - 
> * `Float:size_x` - 
> * `Float:size_y` - 

#### GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:size_x, &Float:size_y)
> Узнать текущие положение хитмаркера
> * `playerid` - The ID of the player
> * `crosshair_type` - [Change position](https://github.com/Bren828/HitMarker-SA-MP#change-position)
> * `&Float:x` - 
> * `&Float:y` - 
> * `&Float:size_x` - 
> * `&Float:size_y` - 

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
  
 
