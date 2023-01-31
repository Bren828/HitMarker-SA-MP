
/*
///////////////////////////////////////////////////////

	Creater - @Bren828 					
									31 January 2023

///////////////////////////////////////////////////////


Включить Hitmarker
	HitmarkerEnabled(playerid);

Выключить Hitmarker
	HitmarkerDisable(playerid);

Узнать статус хитмаркера
	bool:HitmarkerStatus(playerid);
	Вернет: false если выключен
	Вернет: true если включен


Изменить цвет хитмаркера
	HitmarkerColor(playerid, type, color);

Узнать текущий цвет хитмаркера
	GetHitmarkerColor(playerid, type);

Выключить хитмаркер для определенного оружия
	HitmarkerDisableWeapon(playerid, weaponid, bool:disable);
	* При отключении огневого оружия, отключается оружие (ID: 18, 37)
	* При отключении взрывного оружия, отключается оружие (ID: 16, 35, 36, 39, 51) Не распространяется на воздушный транспорт.

Узнать статус хитмаркера у определенного оружия
	GetHitmarkerDisabledWeapon(playerid, weaponid);

Включить звук попадания
	HitmarkerSoundDamage(playerid, soundid);

Узнать текущий звук попадания
	GetHitmarkerSoundDamage(playerid);

Изменить положение хитмаркера 
	HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y);

Узнать текущие положение хитмаркера 
	GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:size_x, &Float:size_y);

Включить индикацию урона по игроку
	HitmarkerEnablePlayerDamage(playerid, bool:enable);
	* По стандарту включено

Узнать статус индикации урона по игроку
	GetHitmarkerEnablePlayerDamage(playerid);

Включить индикацию урона по транспорту
	HitmarkerEnableVehicleDamage(playerid, bool:enable);

Узнать статус индикации урона по транспорту
	GetHitmarkerEnableVehicleDamage(playerid);


/////////////
	Usage
/////////////


CMD:Hitmarker(playerid)
{
	if(HitmarkerStatus(playerid) == false) // Узнаем состояние хитмаркера
	{
		// Включаем хитмаркер
		HitmarkerEnabled(playerid);

		// Устанавливаем нужные цвета попадания
		HitmarkerColor(playerid, HITMARKER_BODYPART_TORSO, 		0xFFFFFFFF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_GROIN, 		0x7CFC00FF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_LEFT_ARM, 	0xFFA500FF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_RIGHT_ARM, 	0xFFD700FF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_LEFT_LEG, 	0x00BFFFFF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_RIGHT_LEG, 	0x00FFFFFF);
		HitmarkerColor(playerid, HITMARKER_BODYPART_HEAD, 		0xFF00FFFF);

		HitmarkerColor(playerid, HITMARKER_KILLSHOTS, 			0xFF0000FF);
		HitmarkerColor(playerid, HITMARKER_VEHICLE_DAMAGE, 		0xB03060FF);

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
*/

#define HITMARKER_KILLSHOTS						0	//При полном убийстве игрока
#define HITMARKER_VEHICLE_DAMAGE				1	//При попадании по транспорту 
#define HITMARKER_BODYPART_TORSO 				3	//При попадании по торсу
#define HITMARKER_BODYPART_GROIN 				4	//При попадании по паху
#define HITMARKER_BODYPART_LEFT_ARM 			5	//При попадании по левой руке
#define HITMARKER_BODYPART_RIGHT_ARM 			6	//При попадании по правой руке
#define HITMARKER_BODYPART_LEFT_LEG 			7	//При попадании по левой ноге 
#define HITMARKER_BODYPART_RIGHT_LEG 			8	//При попадании по правой ноге
#define HITMARKER_BODYPART_HEAD 				9	//При попадании в голову

#define HITMARKER_WEAPON_FIST					0	//Урон получен кулаком
#define HITMARKER_DEATH_UNDER_VEHICLE			50	//Игрок умер под транспортом или от винтов вертолета
#define HITMARKER_ALL_EXPLOSION					51	//Игрок умер от взрыва
#define HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN	52	//Игрок умер от спец оружие воздушного транспорта пулемет
#define HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS	53	//Игрок умер от спец оружие воздушного транспорта ракета

#define HITMARKER_STANDARD_CROSSHAIR 			0	//Изменение положение стандартного прицела
#define HITMARKER_CENTRE_CROSSHAIR 				1	//Изменение положение прицела по центру

#define _Hitmarker_button(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

enum HITMARKER_EN
{
	bool:h_Enabled,
	PlayerText:h_HitTD, h_HitTD_Type, 
	Float:h_CrosshairTD_X, Float:h_CrosshairTD_Y, Float:h_CrosshairTD_SizeX, Float:h_CrosshairTD_SizeY,
	Float:h_CenterCrosshairTD_X, Float:h_CenterCrosshairTD_Y, Float:h_CenterCrosshairTD_SizeX, Float:h_CenterCrosshairTD_SizeY,
	h_ColorBodyParts[10], h_ColorTD,
	bool:h_ShowTD,
	h_ShowTime,
	h_Bodypart,
	h_SpecialAction,
	bool:h_DisableWeapon[54],
	h_SoundDamage, h_SoundDamageDelay,
	h_WeaponIDDamage,
	bool:h_HitType[3], h_HitTypeID,
	h_Timer,
	h_ModeCamera
}
static Hitmarker[MAX_PLAYERS][HITMARKER_EN];
static const NULL_Hitmarker[HITMARKER_EN];


stock HitmarkerEnabled(playerid)
{	
	if(Hitmarker[playerid][h_Enabled] == true) return 0;

	Hitmarker[playerid][h_Enabled] = true;
	Hitmarker[playerid][h_HitTD] = PlayerText:INVALID_TEXT_DRAW;
	for(new x; x < 10; x ++) 
	{
		if(Hitmarker[playerid][h_ColorBodyParts][x] == 0) continue;
		Hitmarker[playerid][h_ColorBodyParts][x] = -1;
	}
	Hitmarker[playerid][h_ShowTD] = false;
	Hitmarker[playerid][h_ShowTime] = 0;
	Hitmarker[playerid][h_Bodypart] = -1;
	Hitmarker[playerid][h_SpecialAction] = -1;
	Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_PLAYER] = true;
	Hitmarker[playerid][h_HitTypeID] = -1;
	Hitmarker[playerid][h_ColorTD] = -1;
	Hitmarker[playerid][h_HitTD_Type] = 0;
	Hitmarker[playerid][h_SoundDamageDelay] = GetTickCount();
	Hitmarker[playerid][h_ModeCamera] = 0;

	new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};
	Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_CrosshairTD_X], Hitmarker[playerid][h_CrosshairTD_Y], _Hit_text);
	PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_CrosshairTD_SizeX], Hitmarker[playerid][h_CrosshairTD_SizeY]);
	PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], -1);
	PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
	PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);

	Hitmarker[playerid][h_Timer] = SetTimerEx("_HitmarkerTimer", 500, true, "d", playerid);
	return 1;
}

stock HitmarkerDisable(playerid)
{	
	if(Hitmarker[playerid][h_Enabled] == false) return 0;

	Hitmarker[playerid][h_Enabled] = false;
	Hitmarker[playerid][h_ShowTD] = false;
	PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_HitTD]);
	Hitmarker[playerid][h_HitTD] = PlayerText:INVALID_TEXT_DRAW;
	KillTimer(Hitmarker[playerid][h_Timer]);
	return 1;
}

stock bool:HitmarkerStatus(playerid)
{
	return Hitmarker[playerid][h_Enabled];
}

stock HitmarkerColor(playerid, type, color)
{
	if(Hitmarker[playerid][h_Enabled] == false || type < 0 || type >= 10 || type == 2) return 0;
	Hitmarker[playerid][h_ColorBodyParts][type] = color;
	return 1;
}

stock GetHitmarkerColor(playerid, type)
{
	if(type < 0 || type >= 10 || type == 2) return 0;
	return Hitmarker[playerid][h_ColorBodyParts][type];
}

stock HitmarkerDisableWeapon(playerid, weaponid, bool:disable)
{
	if(Hitmarker[playerid][h_Enabled] == false || weaponid < 0 || weaponid >= 54) return 0;
	switch(weaponid)
	{
		case 18: Hitmarker[playerid][h_DisableWeapon][37] = disable;
		case 37: Hitmarker[playerid][h_DisableWeapon][18] = disable;
		case 16, 35, 36, 39, 51:
		{
			Hitmarker[playerid][h_DisableWeapon][16] = disable;
			Hitmarker[playerid][h_DisableWeapon][35] = disable;
			Hitmarker[playerid][h_DisableWeapon][36] = disable;
			Hitmarker[playerid][h_DisableWeapon][39] = disable;
			Hitmarker[playerid][h_DisableWeapon][51] = disable;
			return 1;
		}
	}
	Hitmarker[playerid][h_DisableWeapon][weaponid] = disable;
	return 1;
}

stock GetHitmarkerDisabledWeapon(playerid, weaponid)
{
	if(weaponid < 0 || weaponid >= 54) return 0;
	return Hitmarker[playerid][h_DisableWeapon][weaponid];
}

stock HitmarkerSoundDamage(playerid, soundid)
{
	if(Hitmarker[playerid][h_Enabled] == false || soundid < 0 || Hitmarker[playerid][h_ShowTD] == true) return 0;
	Hitmarker[playerid][h_SoundDamage] = soundid;
	return 1;
}

stock GetHitmarkerSoundDamage(playerid)
{
	return Hitmarker[playerid][h_SoundDamage];
}

stock HitmarkerEnablePlayerDamage(playerid, bool:enable)
{
	if(Hitmarker[playerid][h_Enabled] == false) return 0;
	Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_PLAYER] = enable;
	return 1;
}

stock GetHitmarkerEnablePlayerDamage(playerid)
{
	return Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_PLAYER];
}

stock HitmarkerEnableVehicleDamage(playerid, bool:enable)
{
	if(Hitmarker[playerid][h_Enabled] == false) return 0;
	Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE] = enable;
	return 1;
}

stock GetHitmarkerEnableVehicleDamage(playerid)
{
	return Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE];
}

stock HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y)
{
	if(Hitmarker[playerid][h_Enabled] == false || crosshair_type != HITMARKER_STANDARD_CROSSHAIR && crosshair_type != HITMARKER_CENTRE_CROSSHAIR) return 0;
	if(crosshair_type == HITMARKER_CENTRE_CROSSHAIR)
	{
		Hitmarker[playerid][h_CenterCrosshairTD_X] = x; 
		Hitmarker[playerid][h_CenterCrosshairTD_Y] = y;
		Hitmarker[playerid][h_CenterCrosshairTD_SizeX] = size_x; 
		Hitmarker[playerid][h_CenterCrosshairTD_SizeY] = size_y;
	}
	else 
	{
		Hitmarker[playerid][h_CrosshairTD_X] = x;
		Hitmarker[playerid][h_CrosshairTD_Y] = y;
		Hitmarker[playerid][h_CrosshairTD_SizeX] = size_x;
		Hitmarker[playerid][h_CrosshairTD_SizeY] = size_y;
	}
	PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_HitTD]);
	new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};
	Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, x, y, _Hit_text);
	PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], size_x, size_y);
	PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], -1);
	PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
	PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);
	return 1;
}

stock GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:size_x, &Float:size_y)
{
	if(crosshair_type != HITMARKER_STANDARD_CROSSHAIR && crosshair_type != HITMARKER_CENTRE_CROSSHAIR) return 0;
	if(crosshair_type == HITMARKER_CENTRE_CROSSHAIR)
	{
		x = Hitmarker[playerid][h_CenterCrosshairTD_X]; 
		y = Hitmarker[playerid][h_CenterCrosshairTD_Y];
		size_x = Hitmarker[playerid][h_CenterCrosshairTD_SizeX]; 
		size_y = Hitmarker[playerid][h_CenterCrosshairTD_SizeY];
		return 1;
	}
	x = Hitmarker[playerid][h_CrosshairTD_X];
	y = Hitmarker[playerid][h_CrosshairTD_Y];
	size_x = Hitmarker[playerid][h_CrosshairTD_SizeX];
	size_y = Hitmarker[playerid][h_CrosshairTD_SizeY];
	return 1;
}

stock _HitmarkerShowTD(playerid, weaponid)
{
	if(Hitmarker[playerid][h_Enabled] == false) return 0; 

	if(Hitmarker[playerid][h_HitTD_Type] != 0 && (weaponid >= 22 && weaponid <= 33 || weaponid == 38 || GetPlayerCameraMode(playerid) == 53 || GetPlayerCameraMode(playerid) == 55) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		Hitmarker[playerid][h_HitTD_Type] = 0;
		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_HitTD]);

		new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};
		Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_CrosshairTD_X], Hitmarker[playerid][h_CrosshairTD_Y], _Hit_text);
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_CrosshairTD_SizeX], Hitmarker[playerid][h_CrosshairTD_SizeY]);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorTD]);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);
	}
	else if(Hitmarker[playerid][h_HitTD_Type] != 1 && (!(weaponid >= 22 && weaponid <= 33 || weaponid == 38) && GetPlayerCameraMode(playerid) != 53 && GetPlayerCameraMode(playerid) != 55 || GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
	{
		Hitmarker[playerid][h_HitTD_Type] = 1;
		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_HitTD]);

		new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};
		Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_CenterCrosshairTD_X], Hitmarker[playerid][h_CenterCrosshairTD_Y], _Hit_text);
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_CenterCrosshairTD_SizeX], Hitmarker[playerid][h_CenterCrosshairTD_SizeY]);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorTD]);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);
	}
	else PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorTD]);
	PlayerTextDrawShow(playerid, Hitmarker[playerid][h_HitTD]);
	return 1;
}

forward _HitmarkerTimer(playerid);
public _HitmarkerTimer(playerid)
{
	if(Hitmarker[playerid][h_Enabled] == false) return KillTimer(Hitmarker[playerid][h_Timer]);

	if(Hitmarker[playerid][h_ShowTime] != 0 && Hitmarker[playerid][h_ShowTime] <= GetTickCount() ||
		
		Hitmarker[playerid][h_ShowTD] == true && (Hitmarker[playerid][h_WeaponIDDamage] >= 22 && Hitmarker[playerid][h_WeaponIDDamage] <= 34 || Hitmarker[playerid][h_WeaponIDDamage] == 38) && 
		(
			GetPlayerWeaponState(playerid) == WEAPONSTATE_RELOADING && Hitmarker[playerid][h_WeaponIDDamage] != 33 && Hitmarker[playerid][h_WeaponIDDamage] != 34 || 
			GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS || 
			GetPlayerSpecialAction(playerid) != Hitmarker[playerid][h_SpecialAction] || 
			GetPlayerAnimationIndex(playerid) == 1069 || 
			GetPlayerAnimationIndex(playerid) == 1070
		)
	)
	{
		Hitmarker[playerid][h_ShowTD] = false;
		Hitmarker[playerid][h_ShowTime] = 0;
		Hitmarker[playerid][h_Bodypart] = -1;
		Hitmarker[playerid][h_SpecialAction] = -1;
		Hitmarker[playerid][h_ModeCamera] = 0;
		PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
		if(Hitmarker[playerid][h_SoundDamage] != 0) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	}
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID && Hitmarker[issuerid][h_Enabled] == true && GetPlayerState(playerid) != PLAYER_STATE_WASTED && GetPlayerState(issuerid) != PLAYER_STATE_WASTED && Hitmarker[issuerid][h_HitType][BULLET_HIT_TYPE_PLAYER] == true && bodypart >= 3 && bodypart <= 9 && weaponid <= 51)
	{ 
		new bool:check = false;
		if(GetPlayerState(issuerid) == PLAYER_STATE_DRIVER)
		{
			new model = GetVehicleModel(GetPlayerVehicleID(issuerid));
			if((weaponid == 31 && (model == 447 || model == 476 || model == 464) || weaponid == 38 && model == 425) && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN] == true) check = true;
			else if(weaponid == 49 && Hitmarker[issuerid][h_DisableWeapon][WEAPON_VEHICLE] == true) check = true;
			else if(weaponid == 50 && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_DEATH_UNDER_VEHICLE] == true) check = true;
			else if(weaponid == 51 && (model == 425 || model == 520) && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS] == true) check = true;
		}
		else if(Hitmarker[issuerid][h_DisableWeapon][weaponid] == true) check = true;
		
		if(check == false)
		{
			Hitmarker[issuerid][h_ShowTime] = GetTickCount() + 400;
			if(Hitmarker[issuerid][h_ShowTD] == false || Hitmarker[issuerid][h_ShowTD] == true && (Hitmarker[issuerid][h_Bodypart] != bodypart || Hitmarker[issuerid][h_WeaponIDDamage] != weaponid || Hitmarker[issuerid][h_ModeCamera] != GetPlayerCameraMode(issuerid)))
			{
				Hitmarker[issuerid][h_ShowTD] = true;
				Hitmarker[issuerid][h_Bodypart] = bodypart;
				Hitmarker[issuerid][h_WeaponIDDamage] = weaponid;
				Hitmarker[issuerid][h_SpecialAction] = GetPlayerSpecialAction(issuerid);
				Hitmarker[issuerid][h_ModeCamera] = GetPlayerCameraMode(issuerid);
				Hitmarker[issuerid][h_ColorTD] = Hitmarker[issuerid][h_ColorBodyParts][bodypart];
				_HitmarkerShowTD(issuerid, weaponid);
			}
			if(Hitmarker[issuerid][h_SoundDamage] != 0 && Hitmarker[issuerid][h_SoundDamageDelay] <= GetTickCount()) 
			{
				Hitmarker[issuerid][h_SoundDamageDelay] = GetTickCount() + 50;
				PlayerPlaySound(issuerid, Hitmarker[issuerid][h_SoundDamage], 0.0, 0.0, 0.0);
			}
		}
	}
    #if defined OnPlayerTakeDamage_Hitmarker
        OnPlayerTakeDamage_Hitmarker(playerid, issuerid, amount, weaponid, bodypart);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerTakeDamage
    #undef OnPlayerTakeDamage
#else
    #define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage OnPlayerTakeDamage_Hitmarker
#if defined OnPlayerTakeDamage_Hitmarker
    forward OnPlayerTakeDamage_Hitmarker(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID && Hitmarker[killerid][h_Enabled] == true)
	{/*
		* Если игрок убил другого игрока, меняем ему цвет хитмаркера */
		Hitmarker[killerid][h_ShowTD] = true;
		Hitmarker[killerid][h_ShowTime] = GetTickCount() + 400;
		Hitmarker[killerid][h_Bodypart] = -1;
		Hitmarker[killerid][h_WeaponIDDamage] = reason;
		Hitmarker[killerid][h_SpecialAction] = GetPlayerSpecialAction(killerid);
		Hitmarker[killerid][h_ModeCamera] = GetPlayerCameraMode(killerid);
		Hitmarker[killerid][h_ColorTD] = Hitmarker[killerid][h_ColorBodyParts][HITMARKER_KILLSHOTS];
		_HitmarkerShowTD(killerid, reason);
	}
	if(Hitmarker[playerid][h_Enabled] == true && Hitmarker[playerid][h_ShowTD] == true)
	{/* 
		* Игрок который наносил урон умер. Скрываем ему хитмаркер */
		Hitmarker[playerid][h_ShowTD] = false;
		Hitmarker[playerid][h_ShowTime] = 0;
		Hitmarker[playerid][h_Bodypart] = -1;
		Hitmarker[playerid][h_SpecialAction] = -1;
		Hitmarker[playerid][h_ModeCamera] = 0;
		PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
		if(Hitmarker[playerid][h_SoundDamage] != 0) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	}
    #if defined OnPlayerDeath_Hitmarker
        OnPlayerDeath_Hitmarker(playerid, killerid, reason);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath OnPlayerDeath_Hitmarker
#if defined OnPlayerDeath_Hitmarker
    forward OnPlayerDeath_Hitmarker(playerid, killerid, reason);
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(Hitmarker[playerid][h_Enabled] == true && (weaponid >= 22 && weaponid <= 34 || weaponid == 38) && Hitmarker[playerid][h_DisableWeapon][weaponid] == false)
	{
		new carmode = GetPlayerCameraMode(playerid);
	    if((carmode == 4 || carmode == 7 || carmode == 53 || carmode == 55) && hittype >= 1 && hittype <= 2 && Hitmarker[playerid][h_HitType][hittype] == true && Hitmarker[playerid][h_ShowTD] == false && hitid != INVALID_PLAYER_ID && (hittype == BULLET_HIT_TYPE_PLAYER && GetPlayerState(hitid) != PLAYER_STATE_WASTED || hittype == BULLET_HIT_TYPE_VEHICLE /* driver check */) )
	    {
			Hitmarker[playerid][h_ShowTD] = true;
			Hitmarker[playerid][h_ShowTime] = GetTickCount() + 400;
			Hitmarker[playerid][h_WeaponIDDamage] = weaponid;
			Hitmarker[playerid][h_Bodypart] = -1;
			Hitmarker[playerid][h_SpecialAction] = GetPlayerSpecialAction(playerid);
			Hitmarker[playerid][h_HitTypeID] = hittype;
			Hitmarker[playerid][h_ModeCamera] = carmode;
			Hitmarker[playerid][h_ColorTD] = ((hittype == BULLET_HIT_TYPE_PLAYER) ? (-1) : (Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE]));
			_HitmarkerShowTD(playerid, weaponid);
			return 1;
	    }
		else if(Hitmarker[playerid][h_ShowTD] == true)
		{
			if(Hitmarker[playerid][h_HitTypeID] != hittype && Hitmarker[playerid][h_HitType][hittype] == true && (hittype == BULLET_HIT_TYPE_VEHICLE || hittype == BULLET_HIT_TYPE_PLAYER))
			{
				// * Обновляем цвет хитмаркера, если изменился hittype
				Hitmarker[playerid][h_Bodypart] = -1;
				Hitmarker[playerid][h_HitTypeID] = hittype;

				Hitmarker[playerid][h_ColorTD] = ((hittype == BULLET_HIT_TYPE_PLAYER) ? (-1) : (Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE]));
				PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], ((hittype == BULLET_HIT_TYPE_PLAYER) ? (-1) : (Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE])) );
				PlayerTextDrawShow(playerid, Hitmarker[playerid][h_HitTD]);
				return 1;
			}
			else if(Hitmarker[playerid][h_HitTypeID] == hittype && hittype == BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE] == true) 
			{
				Hitmarker[playerid][h_ShowTime] = GetTickCount() + 400;//таймер скрытия TextDraw
				if(Hitmarker[playerid][h_ColorTD] != Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE])
				{
					// * если стрелять в край руки персонажа, и плавно переводить прицел в сторону машины, цвет хитмаркера не будет меняться.
					// * проблема в том что, пуля проходит сквозь персонажа и попадает в транспорт. OnPlayerWeaponShot вызывается раньше чем OnPlayerTakeDamage, и тем самым меняет цвет хитмаркера.
					Hitmarker[playerid][h_ColorTD] = Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE];
					PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE]);
					PlayerTextDrawShow(playerid, Hitmarker[playerid][h_HitTD]);
				}
				return 1;
			}
			else if(Hitmarker[playerid][h_HitTypeID] != hittype)
			{
				Hitmarker[playerid][h_ShowTD] = false;
				Hitmarker[playerid][h_ShowTime] = 0;
				Hitmarker[playerid][h_Bodypart] = -1;
				Hitmarker[playerid][h_SpecialAction] = -1;
				Hitmarker[playerid][h_HitTypeID] = -1;
				Hitmarker[playerid][h_ModeCamera] = 0;
				PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
				if(Hitmarker[playerid][h_SoundDamage] != 0) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
				return 1;
			}
		}
	}
    #if defined OnPlayerWeaponShot_Hitmarker
        OnPlayerWeaponShot_Hitmarker(playerid, weaponid, hittype, hitid, fX, fY, fZ);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot OnPlayerWeaponShot_Hitmarker
#if defined OnPlayerWeaponShot_Hitmarker
    forward OnPlayerWeaponShot_Hitmarker(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

public OnPlayerConnect(playerid)
{
    Hitmarker[playerid] = NULL_Hitmarker;
	Hitmarker[playerid][h_CrosshairTD_X] = 332.5;
	Hitmarker[playerid][h_CrosshairTD_Y] = 172.5;
	Hitmarker[playerid][h_CrosshairTD_SizeX] = 0.33;
	Hitmarker[playerid][h_CrosshairTD_SizeY] = 0.7;

	Hitmarker[playerid][h_CenterCrosshairTD_X] = 310.5; 
	Hitmarker[playerid][h_CenterCrosshairTD_Y] = 214.0;
	Hitmarker[playerid][h_CenterCrosshairTD_SizeX] = 0.46; 
	Hitmarker[playerid][h_CenterCrosshairTD_SizeY] = 1.0;

    #if defined OnPlayerConnect_Hitmarker
        OnPlayerConnect_Hitmarker(playerid);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect OnPlayerConnect_Hitmarker
#if defined OnPlayerConnect_Hitmarker
    forward OnPlayerConnect_Hitmarker(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    if(Hitmarker[playerid][h_Enabled] == true) HitmarkerDisable(playerid);
    #if defined OnPlayerDisconnect_Hitmarker
        OnPlayerDisconnect_Hitmarker(playerid, reason);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect OnPlayerDisconnect_Hitmarker
#if defined OnPlayerDisconnect_Hitmarker
    forward OnPlayerDisconnect_Hitmarker(playerid, reason);
#endif
