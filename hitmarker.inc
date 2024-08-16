
/*
*
*
*
*   ---------------------------------------------------
*
*	Creater - @Bren828 					
*									16 August 2024
*
*   Version: 1.3
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/HitMarker-SA-MP
*
*
*
* Enable hitmarker
*       HitmarkerEnabled(playerid);
*       * playerid: The ID of the player
*	
*	
* Disable hitmarker
*      	HitmarkerDisable(playerid);
*       * playerid: The ID of the player
*	
*	
* Get hitmarker status
*      	bool:HitmarkerStatus(playerid);
*       * playerid: The ID of the player
*	
*      	Return (true) if enabled or (false) if disabled
*	
*	
* Set hitmarker color
*      	HitmarkerColor(playerid, type, color);
* 		* playerid: The ID of the player
*		* type: Color definition
*		* color: The color to set. Supports alpha values.
*	
*	
* Get hitmarker color
*       GetHitmarkerColor(playerid, type);
* 		* playerid: The ID of the player
*		* type: тип цвета
*	
*	    Returns the color
*	
*	
* Disable the hitmarker for a specific weapon
*      	HitmarkerDisableWeapon(playerid, weaponid, bool:disable);
* 		* playerid: The ID of the player
*		* weaponid:  Weapon IDs
*		* bool:disable: true to disable / false to enable
*	
*	
*	
* Get hitmarker status for a certain weapon
*      	GetHitmarkerDisabledWeapon(playerid, weaponid);
* 		* playerid: The ID of the player
*		* weaponid: Weapon IDs
*	
*		* Return (true) if disabled or (false) if enabled
*	
*	
* Enable hit sound
*      	HitmarkerSoundDamage(playerid, soundid);
* 		* playerid: The ID of the player
* 		* soundid: Sound IDs
*	
*	
* Get hit sound
*      	GetHitmarkerSoundDamage(playerid);
* 		* playerid: The ID of the player
*	
*		* Returns sound ID
*	
*	
* Set the marker position
*      	HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y);
* 		* playerid: The ID of the player
* 		* crosshair_type: Position determination
* 		* Float:x: The X (left/right) coordinate to create the textdraw at.
* 		* Float:y: The Y (up/down) coordinate to create the textdraw at.
* 		* Float:size_x: Width
* 		* Float:size_y: Height
*	
*	
* Get hitmarker position
*      	GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:size_x, &Float:size_y);
* 		* playerid: The ID of the player
* 		* crosshair_type: Position determination
* 		* &Float:x: The X (left/right) coordinate
* 		* &Float:y: The Y (up/down) coordinate
* 		* &Float:size_x: Width
* 		* &Float:size_y: Height
*	
*	
* Enable player damage indication
*      	HitmarkerEnablePlayerDamage(playerid, bool:enable);
* 		* playerid: The ID of the player
* 		* bool:enable: true to enable / false to disable
*	
*	
* Get player damage status
*      	GetHitmarkerEnablePlayerDamage(playerid);
* 		* playerid: The ID of the player
*	
*	    * Return (true) if enabled or (false) if disabled
*	
*	
* Enable vehicle damage indication
*      	HitmarkerEnableVehicleDamage(playerid, bool:enable);
* 		* playerid: The ID of the player
* 		* bool:enable: enable - true to enable / false to disable
*	
*	
* Get vehicle damage status
*      	GetHitmarkerEnableVehicleDamage(playerid);
* 		* playerid: The ID of the player
*	
* 		* Вернет: Return (true) if enabled or (false) if disabled
*	
*/

#if defined _hitmarker_included
	#endinput
#endif
#define _hitmarker_included

#if !defined HITMARKER_SHOW_TIME
	#define HITMARKER_SHOW_TIME  	            400 // Hitmarker hide time
#endif

#if !defined HITMARKER_UPDATE_TIMER
	#define HITMARKER_UPDATE_TIMER 	  		 	400 
#endif

#define HITMARKER_KILLSHOTS						0 // at kill shots
#define HITMARKER_VEHICLE_DAMAGE				1 // damage to vehicle 
#define HITMARKER_BODYPART_TORSO 				3 // damage to the right torso
#define HITMARKER_BODYPART_GROIN 				4 // damage to the right groin
#define HITMARKER_BODYPART_LEFT_ARM 			5 // left hand damage
#define HITMARKER_BODYPART_RIGHT_ARM 			6 // right hand damage
#define HITMARKER_BODYPART_LEFT_LEG 			7 // damage to left leg
#define HITMARKER_BODYPART_RIGHT_LEG 			8 // damage to right leg
#define HITMARKER_BODYPART_HEAD 				9 // damage to head

#define HITMARKER_WEAPON_FIST					0  // fist damage
#define HITMARKER_DEATH_UNDER_VEHICLE			50 // the player died under cars or from helicopter rotors
#define HITMARKER_ALL_EXPLOSION					51 // player died from explosion
#define HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN	52 // the player died from a special weapon air transport machine gun
#define HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS	53 // the player died from a special air transport weapon rocket

#define HITMARKER_STANDARD_CROSSHAIR 			0 // standard crosshair position
#define HITMARKER_CENTRE_CROSSHAIR 				1 // centered crosshair position


enum HITMARKER_EN
{
	bool:h_Enabled,
	PlayerText:h_HitTD, 
	h_HitTD_Type, 

	Float:h_CrosshairTD_X, 
	Float:h_CrosshairTD_Y, 
	Float:h_CrosshairTD_SizeX, 
	Float:h_CrosshairTD_SizeY,

	Float:h_CenterCrosshairTD_X, 
	Float:h_CenterCrosshairTD_Y, 
	Float:h_CenterCrosshairTD_SizeX, 
	Float:h_CenterCrosshairTD_SizeY,

	h_ColorBodyParts[10], 
	h_ColorTD,

	bool:h_ShowTD,
	h_ShowTime,
	h_Bodypart,
	h_SpecialAction,

	bool:h_DisableWeapon[54],
	h_SoundDamage, 
	h_SoundDamageDelay,
	h_WeaponIDDamage,

	bool:h_HitType[3], 
	h_HitTypeID,
	h_Timer,
	h_ModeCamera,
	bool:h_Killed
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
		if(Hitmarker[playerid][h_ColorBodyParts][x] == 0) 
			continue;

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
	Hitmarker[playerid][h_Timer] = 0;
	Hitmarker[playerid][h_Killed] = false;

	new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};

	Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_CrosshairTD_X], Hitmarker[playerid][h_CrosshairTD_Y], _Hit_text);
	PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
	PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_CrosshairTD_SizeX], Hitmarker[playerid][h_CrosshairTD_SizeY]);
	PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], -1);
	PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
	PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);
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
	Hitmarker[playerid][h_Timer] = 0;
	return 1;
}

stock bool:HitmarkerStatus(playerid)
{
	return Hitmarker[playerid][h_Enabled];
}

stock HitmarkerColor(playerid, type, color)
{
	if(type < 0 || type >= 10 || type == 2) return 0;
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
	if(weaponid < 0 || weaponid >= 54) return 0;

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
	if(soundid < 0) return 0;

	Hitmarker[playerid][h_SoundDamage] = soundid;
	return 1;
}

stock GetHitmarkerSoundDamage(playerid)
{
	return Hitmarker[playerid][h_SoundDamage];
}

stock HitmarkerEnablePlayerDamage(playerid, bool:enable)
{
	Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_PLAYER] = enable;
	return 1;
}

stock GetHitmarkerEnablePlayerDamage(playerid)
{
	return Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_PLAYER];
}

stock HitmarkerEnableVehicleDamage(playerid, bool:enable)
{
	Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE] = enable;
	return 1;
}

stock GetHitmarkerEnableVehicleDamage(playerid)
{
	return Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE];
}

stock HitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:size_x, Float:size_y)
{
	if(crosshair_type != HITMARKER_STANDARD_CROSSHAIR && crosshair_type != HITMARKER_CENTRE_CROSSHAIR) return 0;

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

	if(Hitmarker[playerid][h_Enabled] == true)
	{
		new _Hit_text[11] = {92, 1, 47, 126, 110, 126, 47, 1, 92};

		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_HitTD]);
		Hitmarker[playerid][h_HitTD] = CreatePlayerTextDraw(playerid, x, y, _Hit_text);
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_HitTD], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_HitTD], size_x, size_y);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], -1);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_HitTD], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_HitTD], 1);
	}
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

static stock _HitmarkerShowTD(playerid, weaponid)
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
	if(Hitmarker[playerid][h_ShowTime] != 0 && Hitmarker[playerid][h_ShowTime] <= GetTickCount() ||
		Hitmarker[playerid][h_ShowTD] == true && (Hitmarker[playerid][h_WeaponIDDamage] >= 22 && Hitmarker[playerid][h_WeaponIDDamage] <= 34 || 
		Hitmarker[playerid][h_WeaponIDDamage] == 38) && 

		(GetPlayerWeaponState(playerid) == WEAPONSTATE_RELOADING && Hitmarker[playerid][h_WeaponIDDamage] != 33 && Hitmarker[playerid][h_WeaponIDDamage] != 34 || 
		GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS || 
		GetPlayerSpecialAction(playerid) != Hitmarker[playerid][h_SpecialAction] || 
		GetPlayerAnimationIndex(playerid) == 1069 || 
		GetPlayerAnimationIndex(playerid) == 1070))
	{
		Hitmarker[playerid][h_ShowTD] = false;
		Hitmarker[playerid][h_ShowTime] = 0;
		Hitmarker[playerid][h_Bodypart] = -1;
		Hitmarker[playerid][h_SpecialAction] = -1;
		Hitmarker[playerid][h_ModeCamera] = 0;
		Hitmarker[playerid][h_Timer] = 0;
		Hitmarker[playerid][h_Killed] = false;

		PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
		if(Hitmarker[playerid][h_SoundDamage] != 0 && Hitmarker[playerid][h_SoundDamage] != 17802) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
		return 1;
	}

	if(Hitmarker[playerid][h_ShowTime] >= GetTickCount()) Hitmarker[playerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_UPDATE_TIMER, false, "d", playerid);
	else Hitmarker[playerid][h_Timer] = 0;
	return 1;
}


#if defined _INC_WEAPON_CONFIG 
	public OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart)
{
	new weaponid = weapon;
#elseif defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
#else
	public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
#endif
    if(issuerid != INVALID_PLAYER_ID && Hitmarker[issuerid][h_Enabled] == true && GetPlayerState(playerid) != PLAYER_STATE_WASTED && GetPlayerState(issuerid) != PLAYER_STATE_WASTED && Hitmarker[issuerid][h_HitType][BULLET_HIT_TYPE_PLAYER] == true && bodypart >= 3 && bodypart <= 9 && weaponid <= 51)
	{ 
		new bool:hide_td = false;
		if(GetPlayerState(issuerid) == PLAYER_STATE_DRIVER)
		{
			new model = GetVehicleModel(GetPlayerVehicleID(issuerid));
			if((weaponid == 31 && (model == 447 || model == 476 || model == 464) || weaponid == 38 && model == 425) && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_AIR_VEHICLE_WEAPON_MINIGUN] == true) hide_td = true;
			else if(weaponid == 49 && Hitmarker[issuerid][h_DisableWeapon][WEAPON_VEHICLE] == true) hide_td = true;
			else if(weaponid == 50 && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_DEATH_UNDER_VEHICLE] == true) hide_td = true;
			else if(weaponid == 51 && (model == 425 || model == 520) && Hitmarker[issuerid][h_DisableWeapon][HITMARKER_AIR_VEHICLE_WEAPON_ROCKETS] == true) hide_td = true;
		}
		else if(Hitmarker[issuerid][h_DisableWeapon][weaponid] == true) hide_td = true;
		
		if(hide_td == false)
		{
			Hitmarker[issuerid][h_ShowTime] = GetTickCount() + HITMARKER_SHOW_TIME;

			if(Hitmarker[issuerid][h_ShowTD] == false || 
				Hitmarker[issuerid][h_ShowTD] == true && 
				(Hitmarker[issuerid][h_Bodypart] != bodypart || Hitmarker[issuerid][h_WeaponIDDamage] != weaponid || Hitmarker[issuerid][h_ModeCamera] != GetPlayerCameraMode(issuerid)))
			{
				Hitmarker[issuerid][h_ShowTD] = true;
				if(Hitmarker[issuerid][h_Timer] == 0) Hitmarker[issuerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_UPDATE_TIMER, false, "d", issuerid);
				Hitmarker[issuerid][h_Bodypart] = bodypart;
				Hitmarker[issuerid][h_WeaponIDDamage] = weaponid;
				Hitmarker[issuerid][h_HitTypeID] = BULLET_HIT_TYPE_PLAYER;
				Hitmarker[issuerid][h_SpecialAction] = GetPlayerSpecialAction(issuerid);
				Hitmarker[issuerid][h_ModeCamera] = GetPlayerCameraMode(issuerid);
				Hitmarker[issuerid][h_ColorTD] = Hitmarker[issuerid][h_ColorBodyParts][bodypart];
				_HitmarkerShowTD(issuerid, weaponid);
			}
			
		}
	}

	if(issuerid != INVALID_PLAYER_ID && 
		Hitmarker[issuerid][h_SoundDamage] != 0 && 
		Hitmarker[issuerid][h_SoundDamageDelay] <= GetTickCount() && 
		GetPlayerState(playerid) != PLAYER_STATE_WASTED && 
		bodypart >= 3 && bodypart <= 9 && weaponid <= 51) 
	{
		Hitmarker[issuerid][h_SoundDamageDelay] = GetTickCount() + 50;
		PlayerPlaySound(issuerid, Hitmarker[issuerid][h_SoundDamage], 0.0, 0.0, 0.0);
	}

	#if defined _INC_WEAPON_CONFIG && defined OnPlayerDamageDone_Hitmarker
		return OnPlayerDamageDone_Hitmarker(playerid, amount, issuerid, weapon, bodypart);

    #elseif !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerTakeDamage_Hitmarker
		return OnPlayerTakeDamage_Hitmarker(playerid, issuerid, amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}

#if defined _INC_WEAPON_CONFIG

	#if defined _ALS_OnPlayerDamageDone
		#undef OnPlayerDamageDone
	#else
		#define _ALS_OnPlayerDamageDone
	#endif
	#define OnPlayerDamageDone OnPlayerDamageDone_Hitmarker
	#if defined OnPlayerDamageDone_Hitmarker
		forward OnPlayerDamageDone_Hitmarker(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart);
	#endif

#elseif !defined _inc_y_hooks && !defined _INC_y_hooks

	#if defined _ALS_OnPlayerTakeDamage
		#undef OnPlayerTakeDamage
	#else
		#define _ALS_OnPlayerTakeDamage
	#endif
	#define OnPlayerTakeDamage OnPlayerTakeDamage_Hitmarker
	#if defined OnPlayerTakeDamage_Hitmarker
		forward OnPlayerTakeDamage_Hitmarker(playerid, issuerid, Float:amount, weaponid, bodypart);
	#endif
	
#endif


#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerDeath(playerid, killerid, reason)
#else
	public OnPlayerDeath(playerid, killerid, reason)
#endif
{
    if(killerid != INVALID_PLAYER_ID && Hitmarker[killerid][h_Enabled] == true)
	{/*
		* change color when lshdd kill shots */
		Hitmarker[killerid][h_ShowTD] = true;
		if(Hitmarker[killerid][h_Timer] == 0) Hitmarker[killerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_UPDATE_TIMER, false, "d", killerid);
		Hitmarker[killerid][h_ShowTime] = GetTickCount() + HITMARKER_SHOW_TIME;
		Hitmarker[killerid][h_Bodypart] = -1;
		Hitmarker[killerid][h_WeaponIDDamage] = reason;
		Hitmarker[killerid][h_SpecialAction] = GetPlayerSpecialAction(killerid);
		Hitmarker[killerid][h_ModeCamera] = GetPlayerCameraMode(killerid);
		Hitmarker[killerid][h_ColorTD] = Hitmarker[killerid][h_ColorBodyParts][HITMARKER_KILLSHOTS];
		Hitmarker[killerid][h_Killed] = true;
		_HitmarkerShowTD(killerid, reason);
	}

	if(Hitmarker[playerid][h_Enabled] == true && Hitmarker[playerid][h_ShowTD] == true)
	{
		Hitmarker[playerid][h_ShowTD] = false;
		Hitmarker[playerid][h_ShowTime] = 0;
		Hitmarker[playerid][h_Bodypart] = -1;
		Hitmarker[playerid][h_SpecialAction] = -1;
		Hitmarker[playerid][h_ModeCamera] = 0;
		Hitmarker[killerid][h_Killed] = false;
		PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
		if(Hitmarker[playerid][h_SoundDamage] != 0 && Hitmarker[playerid][h_SoundDamage] != 17802) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	}

    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerDeath_Hitmarker
		return OnPlayerDeath_Hitmarker(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerDeath
		#undef OnPlayerDeath
	#else
		#define _ALS_OnPlayerDeath
	#endif
	#define OnPlayerDeath OnPlayerDeath_Hitmarker
	#if defined OnPlayerDeath_Hitmarker
		forward OnPlayerDeath_Hitmarker(playerid, killerid, reason);
	#endif
#endif



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
#else
	public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
#endif
{
	if(Hitmarker[playerid][h_Enabled] == true && (weaponid >= 22 && weaponid <= 34 || weaponid == 38) && Hitmarker[playerid][h_DisableWeapon][weaponid] == false)
	{
		new carmode = GetPlayerCameraMode(playerid),
			color;

		if(hittype == BULLET_HIT_TYPE_PLAYER) color = Hitmarker[playerid][h_ColorBodyParts][HITMARKER_BODYPART_TORSO];
		else color = Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE];

		if(hittype == BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitType][hittype] == true && hitid != INVALID_PLAYER_ID && Hitmarker[playerid][h_ShowTD] == false)
		{
			Hitmarker[playerid][h_ShowTD] = true;
			
			if(Hitmarker[playerid][h_Timer] == 0) Hitmarker[playerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_UPDATE_TIMER, false, "d", playerid);
			Hitmarker[playerid][h_ShowTime] = GetTickCount() + HITMARKER_SHOW_TIME;

			Hitmarker[playerid][h_WeaponIDDamage] = weaponid;
			Hitmarker[playerid][h_Bodypart] = -1;
			Hitmarker[playerid][h_SpecialAction] = GetPlayerSpecialAction(playerid);
			Hitmarker[playerid][h_HitTypeID] = hittype;
			Hitmarker[playerid][h_ModeCamera] = carmode;
			Hitmarker[playerid][h_ColorTD] = color;

			_HitmarkerShowTD(playerid, weaponid);
		}
		else if(Hitmarker[playerid][h_ShowTD] == true)
		{
			if(Hitmarker[playerid][h_HitTypeID] != hittype && hittype >= BULLET_HIT_TYPE_PLAYER && hittype <= BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitType][hittype] == true)
			{
				// * Update the hitmarker color if the hittype has changed
				Hitmarker[playerid][h_Bodypart] = -1;
				Hitmarker[playerid][h_HitTypeID] = hittype;
				Hitmarker[playerid][h_ColorTD] = color;

				PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorTD]);
				PlayerTextDrawShow(playerid, Hitmarker[playerid][h_HitTD]);
			}
			else if(Hitmarker[playerid][h_HitTypeID] == hittype && hittype == BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitType][BULLET_HIT_TYPE_VEHICLE] == true) 
			{
				Hitmarker[playerid][h_ShowTime] = GetTickCount() + HITMARKER_SHOW_TIME;//таймер скрытия TextDraw
				if(Hitmarker[playerid][h_ColorTD] != Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE])
				{
					Hitmarker[playerid][h_ColorTD] = Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE];
					PlayerTextDrawColor(playerid, Hitmarker[playerid][h_HitTD], Hitmarker[playerid][h_ColorBodyParts][HITMARKER_VEHICLE_DAMAGE]);
					PlayerTextDrawShow(playerid, Hitmarker[playerid][h_HitTD]);
				}
			}
			else if(Hitmarker[playerid][h_HitTypeID] != hittype && Hitmarker[playerid][h_Killed] == false)
			{
				Hitmarker[playerid][h_ShowTD] = false;
				Hitmarker[playerid][h_ShowTime] = 0;
				Hitmarker[playerid][h_Bodypart] = -1;
				Hitmarker[playerid][h_SpecialAction] = -1;
				Hitmarker[playerid][h_HitTypeID] = -1;
				Hitmarker[playerid][h_ModeCamera] = 0;
				Hitmarker[playerid][h_Killed] = false;
				PlayerTextDrawHide(playerid, Hitmarker[playerid][h_HitTD]);
				if(Hitmarker[playerid][h_SoundDamage] != 0 && Hitmarker[playerid][h_SoundDamage] != 17802) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
			}
		}
	}
    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerWeaponShot_Hitmarker
		return OnPlayerWeaponShot_Hitmarker(playerid, weaponid, hittype, hitid, fX, fY, fZ);
	#else
		return 1;
	#endif
}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerWeaponShot
		#undef OnPlayerWeaponShot
	#else
		#define _ALS_OnPlayerWeaponShot
	#endif
	#define OnPlayerWeaponShot OnPlayerWeaponShot_Hitmarker
	#if defined OnPlayerWeaponShot_Hitmarker
		forward OnPlayerWeaponShot_Hitmarker(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#endif
#endif



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerConnect(playerid)
#else
	public OnPlayerConnect(playerid)
#endif
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

    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerConnect_Hitmarker
		return OnPlayerConnect_Hitmarker(playerid);
	#else
		return 1;
	#endif
}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect OnPlayerConnect_Hitmarker
	#if defined OnPlayerConnect_Hitmarker
		forward OnPlayerConnect_Hitmarker(playerid);
	#endif
#endif



#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnPlayerDisconnect(playerid, reason)
#else
	public OnPlayerDisconnect(playerid, reason)
#endif
{
    if(Hitmarker[playerid][h_Enabled] == true) HitmarkerDisable(playerid);

    #if !defined _inc_y_hooks && !defined _INC_y_hooks && defined OnPlayerDisconnect_Hitmarker
		return OnPlayerDisconnect_Hitmarker(playerid, reason);
	#else
		return 1;
	#endif
}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect OnPlayerDisconnect_Hitmarker
	#if defined OnPlayerDisconnect_Hitmarker
		forward OnPlayerDisconnect_Hitmarker(playerid, reason);
	#endif
#endif
