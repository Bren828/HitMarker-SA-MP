
/*
*
*
*
*   ---------------------------------------------------
*
*	Created by Bren828 					
*									02 May 2026
*
*   Version: 1.4
*
*   ---------------------------------------------------
*
*
*	https://github.com/Bren828/HitMarker-SA-MP
*
*
*/

#if defined _hitmarker_included
	#endinput
#endif
#define _hitmarker_included


#if !defined HITMARKER_VISIBLE_TIME
	#define HITMARKER_VISIBLE_TIME 400
#endif

#if !defined HITMARKER_TICK_RATE
	#define HITMARKER_TICK_RATE 400 
#endif


enum {
	HITMARKER_COLOR_KILLSHOT = 0,
	HITMARKER_COLOR_VEHICLE = 1,

	HITMARKER_BODYPART_TORSO = 3,
	HITMARKER_BODYPART_GROIN = 4,
	HITMARKER_BODYPART_LEFT_ARM = 5,
	HITMARKER_BODYPART_RIGHT_ARM = 6,
	HITMARKER_BODYPART_LEFT_LEG = 7, 
	HITMARKER_BODYPART_RIGHT_LEG = 8,
	HITMARKER_BODYPART_HEAD = 9,

	HITMARKER_WEAPON_FIST = 0,
	HITMARKER_WEAPON_VEHICLE_CRUSH = 50,
	HITMARKER_ALL_EXPLOSION	= 51,
	HITMARKER_AIR_WEAPON_MINIGUN = 52,
	HITMARKER_AIR_WEAPON_ROCKETS = 53,

	HITMARKER_POS_STANDARD = 0,
	HITMARKER_POS_CENTER = 1
}


enum E_HITMARKER {

	bool:h_Enabled,

	PlayerText:h_TextDraw, 
	h_PosType, 

	Float:h_X, 
	Float:h_Y, 
	Float:h_SizeX, 
	Float:h_SizeY,

	Float:h_CenterX, 
	Float:h_CenterY, 
	Float:h_CenterSizeX, 
	Float:h_CenterSizeY,

	bool:h_Visible,
	h_Color,
	h_HitColors[10],

	h_ShowTime,
	h_BodyPart,
	h_LastSpecialAction,

	bool:h_DisabledWeapons[54],
	h_SoundDamage, 
	h_SoundDamageDelay,
	h_WeaponDamage,

	bool:h_HitTypeEnabled[3], 
	h_HitType,
	h_Timer,
	h_LastCameraMode,
	bool:h_Killed
}

static Hitmarker[MAX_PLAYERS][E_HITMARKER];
static const NULL_Hitmarker[E_HITMARKER];



stock HitmarkerEnable(playerid) {

	if(IsHitmarkerEnabled(playerid)) {
		return 0;
	}

	Hitmarker[playerid][h_Enabled] = true;
	Hitmarker[playerid][h_TextDraw] = PlayerText:INVALID_TEXT_DRAW;

	for(new i; i < 10; i ++) {
		if(Hitmarker[playerid][h_HitColors][i] == 0) {
			continue;
		}
		Hitmarker[playerid][h_HitColors][i] = -1;
	}

	Hitmarker[playerid][h_Visible] = false;
	Hitmarker[playerid][h_ShowTime] = 0;
	Hitmarker[playerid][h_BodyPart] = -1;
	Hitmarker[playerid][h_LastSpecialAction] = -1;
	Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_PLAYER] = true;
	Hitmarker[playerid][h_HitType] = -1;
	Hitmarker[playerid][h_Color] = -1;
	Hitmarker[playerid][h_PosType] = 0;
	Hitmarker[playerid][h_SoundDamageDelay] = GetTickCount();
	Hitmarker[playerid][h_LastCameraMode] = 0;
	Hitmarker[playerid][h_Timer] = 0;
	Hitmarker[playerid][h_Killed] = false;

	Hitmarker[playerid][h_TextDraw] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_X], Hitmarker[playerid][h_Y], "\\/~n~/\\");
	PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_TextDraw], 0);
	PlayerTextDrawFont(playerid, Hitmarker[playerid][h_TextDraw], 0);
	PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_SizeX], Hitmarker[playerid][h_SizeY]);
	PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], -1);
	PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_TextDraw], 1);
	PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_TextDraw], 1);
	return 1;
}


stock HitmarkerDisable(playerid) {

	if(!IsHitmarkerEnabled(playerid)) {
		return 0;
	}

	Hitmarker[playerid][h_Enabled] = false;
	Hitmarker[playerid][h_Visible] = false;

	PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_TextDraw]);
	Hitmarker[playerid][h_TextDraw] = PlayerText:INVALID_TEXT_DRAW;

	KillTimer(Hitmarker[playerid][h_Timer]);
	Hitmarker[playerid][h_Timer] = 0;
	return 1;
}


stock IsHitmarkerEnabled(playerid) {
	return Hitmarker[playerid][h_Enabled];
}


stock SetHitmarkerColor(playerid, type, color) {

	if(type < 0 || type >= 10 || type == 2) {
		return 0;
	}
	
	Hitmarker[playerid][h_HitColors][type] = color;
	return 1;
}


stock GetHitmarkerColor(playerid, type) {

	if(type < 0 || type >= 10 || type == 2) {
		return 0;
	}
	
	return Hitmarker[playerid][h_HitColors][type];
}


stock ToggleHitmarkerWeapon(playerid, weaponid, bool:toggle) {

	if(weaponid < 0 || weaponid >= 54) {
		return 0;
	}

	switch(weaponid) {
		case 18: { 
			Hitmarker[playerid][h_DisabledWeapons][37] = toggle;
		}
		case 37: { 
			Hitmarker[playerid][h_DisabledWeapons][18] = toggle;
		}
		case 16, 35, 36, 39, 51: {
			Hitmarker[playerid][h_DisabledWeapons][16] = toggle;
			Hitmarker[playerid][h_DisabledWeapons][35] = toggle;
			Hitmarker[playerid][h_DisabledWeapons][36] = toggle;
			Hitmarker[playerid][h_DisabledWeapons][39] = toggle;
			Hitmarker[playerid][h_DisabledWeapons][51] = toggle;
			return 1;
		}
	}

	Hitmarker[playerid][h_DisabledWeapons][weaponid] = toggle;
	return 1;
}


stock IsHitmarkerWeaponDisabled(playerid, weaponid) {

	if(weaponid < 0 || weaponid >= 54) {
		return 0;
	}

	return Hitmarker[playerid][h_DisabledWeapons][weaponid];
}


stock SetHitmarkerSoundDamage(playerid, soundid) {

	if(soundid < 0) {
		return 0;
	}

	Hitmarker[playerid][h_SoundDamage] = soundid;
	return 1;
}


stock GetHitmarkerSoundDamage(playerid) {
	return Hitmarker[playerid][h_SoundDamage];
}


stock ToggleHitmarkerPlayerDamage(playerid, bool:toggle) {
	Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_PLAYER] = toggle;
	return 1;
}


stock IsHitmarkerPlayerDamageEnabled(playerid) {
	return Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_PLAYER];
}


stock ToggleHitmarkerVehicleDamage(playerid, bool:toggle) {
	Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_VEHICLE] = toggle;
	return 1;
}


stock IsHitmarkerVehicleDamageEnabled(playerid) {
	return Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_VEHICLE];
}


stock SetHitmarkerPosition(playerid, crosshair_type, Float:x, Float:y, Float:sizeX, Float:sizeY) {

	if(crosshair_type != HITMARKER_POS_STANDARD && crosshair_type != HITMARKER_POS_CENTER) {
		return 0;
	}

	if(crosshair_type == HITMARKER_POS_CENTER) {
		Hitmarker[playerid][h_CenterX] = x; 
		Hitmarker[playerid][h_CenterY] = y;
		Hitmarker[playerid][h_CenterSizeX] = sizeX; 
		Hitmarker[playerid][h_CenterSizeY] = sizeY;
	}
	else {
		Hitmarker[playerid][h_X] = x;
		Hitmarker[playerid][h_Y] = y;
		Hitmarker[playerid][h_SizeX] = sizeX;
		Hitmarker[playerid][h_SizeY] = sizeY;
	}

	if(IsHitmarkerEnabled(playerid)) {
		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_TextDraw]);

		Hitmarker[playerid][h_TextDraw] = CreatePlayerTextDraw(playerid, x, y, "\\/~n~/\\");
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_TextDraw], sizeX, sizeY);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], -1);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_TextDraw], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_TextDraw], 1);
	}
	return 1;
}


stock GetHitmarkerPosition(playerid, crosshair_type, &Float:x, &Float:y, &Float:sizeX, &Float:sizeY) {

	if(crosshair_type != HITMARKER_POS_STANDARD && crosshair_type != HITMARKER_POS_CENTER) {
		return 0;
	}

	if(crosshair_type == HITMARKER_POS_CENTER) {
		x = Hitmarker[playerid][h_CenterX]; 
		y = Hitmarker[playerid][h_CenterY];

		sizeX = Hitmarker[playerid][h_CenterSizeX]; 
		sizeY = Hitmarker[playerid][h_CenterSizeY];
	}
	else {
		x = Hitmarker[playerid][h_X];
		y = Hitmarker[playerid][h_Y];

		sizeX = Hitmarker[playerid][h_SizeX];
		sizeY = Hitmarker[playerid][h_SizeY];
	}
	return 1;
}


stock static _ShowHitmarker(playerid, weaponid, hittype, color, bodypart) {

	Hitmarker[playerid][h_Visible] = true;
	
	if(!Hitmarker[playerid][h_Timer]) {
		Hitmarker[playerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_TICK_RATE, false, "d", playerid);
	}

	Hitmarker[playerid][h_WeaponDamage] = weaponid;
	Hitmarker[playerid][h_HitType] = hittype;
	Hitmarker[playerid][h_Color] = color;

	if(bodypart != -1) {
		Hitmarker[playerid][h_BodyPart] = bodypart;
	}

	Hitmarker[playerid][h_LastSpecialAction] = GetPlayerSpecialAction(playerid);
	Hitmarker[playerid][h_LastCameraMode] = GetPlayerCameraMode(playerid);
	Hitmarker[playerid][h_ShowTime] = GetTickCount() + HITMARKER_VISIBLE_TIME;

	_CreateHitmarkerTextDraw(playerid, weaponid);
	return 1;
}


stock static _HideHitmarker(playerid) {

	if(!Hitmarker[playerid][h_Visible]) {
		return 0;
	}

	Hitmarker[playerid][h_Visible] = false;
	Hitmarker[playerid][h_ShowTime] = 0;
	Hitmarker[playerid][h_BodyPart] = -1;
	Hitmarker[playerid][h_LastSpecialAction] = -1;
	Hitmarker[playerid][h_LastCameraMode] = 0;
	Hitmarker[playerid][h_Killed] = false;
	Hitmarker[playerid][h_HitType] = -1;

	PlayerTextDrawHide(playerid, Hitmarker[playerid][h_TextDraw]);

	if(Hitmarker[playerid][h_SoundDamage] != 0 && Hitmarker[playerid][h_SoundDamage] != 17802) {
		PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	}

	return 1;
}


static stock _CreateHitmarkerTextDraw(playerid, weaponid) {

	if(!IsHitmarkerEnabled(playerid)) {
		return 0; 
	}

	new cameraMode = GetPlayerCameraMode(playerid);

	if(Hitmarker[playerid][h_PosType] != 0 && (weaponid >= 22 && weaponid <= 33 || weaponid == 38 || cameraMode == 53 || cameraMode == 55) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		Hitmarker[playerid][h_PosType] = 0;
		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_TextDraw]);

		Hitmarker[playerid][h_TextDraw] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_X], Hitmarker[playerid][h_Y], "\\/~n~/\\");
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_SizeX], Hitmarker[playerid][h_SizeY]);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_Color]);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_TextDraw], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_TextDraw], 1);
	}
	else if(Hitmarker[playerid][h_PosType] != 1 && (!(weaponid >= 22 && weaponid <= 33 || weaponid == 38) && cameraMode != 53 && cameraMode != 55 || GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
	{
		Hitmarker[playerid][h_PosType] = 1;
		PlayerTextDrawDestroy(playerid, Hitmarker[playerid][h_TextDraw]);

		Hitmarker[playerid][h_TextDraw] = CreatePlayerTextDraw(playerid, Hitmarker[playerid][h_CenterX], Hitmarker[playerid][h_CenterY], "\\/~n~/\\");
		PlayerTextDrawBackgroundColor(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawFont(playerid, Hitmarker[playerid][h_TextDraw], 0);
		PlayerTextDrawLetterSize(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_CenterSizeX], Hitmarker[playerid][h_CenterSizeY]);
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_Color]);
		PlayerTextDrawSetProportional(playerid, Hitmarker[playerid][h_TextDraw], 1);
		PlayerTextDrawSetShadow(playerid, Hitmarker[playerid][h_TextDraw], 1);
	}
	else {
		PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_Color]);
	}

	PlayerTextDrawShow(playerid, Hitmarker[playerid][h_TextDraw]);
	return 1;
}


forward _HitmarkerTimer(playerid);
public _HitmarkerTimer(playerid) {

	if(Hitmarker[playerid][h_ShowTime] != 0 && Hitmarker[playerid][h_ShowTime] <= GetTickCount() ||
	   Hitmarker[playerid][h_Visible] == true && (Hitmarker[playerid][h_WeaponDamage] >= 22 && Hitmarker[playerid][h_WeaponDamage] <= 34 || 
	   Hitmarker[playerid][h_WeaponDamage] == 38) && 

		(GetPlayerWeaponState(playerid) == WEAPONSTATE_RELOADING && Hitmarker[playerid][h_WeaponDamage] != 33 && Hitmarker[playerid][h_WeaponDamage] != 34 || 
		GetPlayerWeaponState(playerid) == WEAPONSTATE_NO_BULLETS || 
		GetPlayerSpecialAction(playerid) != Hitmarker[playerid][h_LastSpecialAction] || 
		GetPlayerAnimationIndex(playerid) == 1069 || 
		GetPlayerAnimationIndex(playerid) == 1070))
	{
		Hitmarker[playerid][h_Timer] = 0;
		_HideHitmarker(playerid);
		return 1;
	}
	
	if(Hitmarker[playerid][h_ShowTime] >= GetTickCount()) {
		Hitmarker[playerid][h_Timer] = SetTimerEx("_HitmarkerTimer", HITMARKER_TICK_RATE, false, "d", playerid);
	}
	else {
		Hitmarker[playerid][h_Timer] = 0;
	}

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

    if(issuerid != INVALID_PLAYER_ID && 
	   IsHitmarkerEnabled(issuerid) && 
	   GetPlayerState(playerid) != PLAYER_STATE_WASTED && GetPlayerState(issuerid) != PLAYER_STATE_WASTED && 
	   Hitmarker[issuerid][h_HitTypeEnabled][BULLET_HIT_TYPE_PLAYER] && bodypart >= 3 && bodypart <= 9 && weaponid <= 51)
	{ 
		new bool:hideTextDraw = false;

		if(GetPlayerState(issuerid) == PLAYER_STATE_DRIVER) {

			new model = GetVehicleModel(GetPlayerVehicleID(issuerid));

			if((weaponid == 31 && (model == 447 || model == 476 || model == 464) || weaponid == 38 && model == 425) && Hitmarker[issuerid][h_DisabledWeapons][HITMARKER_AIR_WEAPON_MINIGUN]) {
				hideTextDraw = true;
			}
			else if(weaponid == 49 && Hitmarker[issuerid][h_DisabledWeapons][WEAPON_VEHICLE]) {
				hideTextDraw = true;
			}
			else if(weaponid == 50 && Hitmarker[issuerid][h_DisabledWeapons][HITMARKER_WEAPON_VEHICLE_CRUSH]) {
				hideTextDraw = true;
			}
			else if(weaponid == 51 && (model == 425 || model == 520) && Hitmarker[issuerid][h_DisabledWeapons][HITMARKER_AIR_WEAPON_ROCKETS]) {
				hideTextDraw = true;
			}
		}
		else if(Hitmarker[issuerid][h_DisabledWeapons][weaponid]) {
			hideTextDraw = true;
		}

		if(hideTextDraw == false) {
			Hitmarker[issuerid][h_ShowTime] = GetTickCount() + HITMARKER_VISIBLE_TIME;

			if(!Hitmarker[issuerid][h_Visible] || Hitmarker[issuerid][h_Visible]) {

				if(Hitmarker[issuerid][h_BodyPart] != bodypart || 
				   Hitmarker[issuerid][h_WeaponDamage] != weaponid || 
				   Hitmarker[issuerid][h_LastCameraMode] != GetPlayerCameraMode(issuerid)) {
					_ShowHitmarker(issuerid, weaponid, BULLET_HIT_TYPE_PLAYER, Hitmarker[issuerid][h_HitColors][bodypart], bodypart);
				}
			}
		}
	}

	if(issuerid != INVALID_PLAYER_ID && 
	   Hitmarker[issuerid][h_SoundDamage] != 0 && Hitmarker[issuerid][h_SoundDamageDelay] <= GetTickCount() && 
	   GetPlayerState(playerid) != PLAYER_STATE_WASTED && bodypart >= 3 && bodypart <= 9 && weaponid <= 51) 
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
    if(killerid != INVALID_PLAYER_ID && IsHitmarkerEnabled(killerid)) {
		// change color when lshdd kill shots

		Hitmarker[killerid][h_Killed] = true;
		_ShowHitmarker(killerid, reason, -1, Hitmarker[killerid][h_HitColors][HITMARKER_COLOR_KILLSHOT], .bodypart = -1);
	}

	if(IsHitmarkerEnabled(playerid) && Hitmarker[playerid][h_Visible]) {
		_HideHitmarker(playerid);
		Hitmarker[killerid][h_Killed] = false;
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
	if(IsHitmarkerEnabled(playerid) && (weaponid >= 22 && weaponid <= 34 || weaponid == 38) && !Hitmarker[playerid][h_DisabledWeapons][weaponid] && !Hitmarker[playerid][h_Killed]) {

		new color = (hittype == BULLET_HIT_TYPE_PLAYER) ? 
			(Hitmarker[playerid][h_HitColors][HITMARKER_BODYPART_TORSO]) : 
			(Hitmarker[playerid][h_HitColors][HITMARKER_COLOR_VEHICLE]);

		if(hittype == BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitTypeEnabled][hittype] && hitid != INVALID_PLAYER_ID && !Hitmarker[playerid][h_Visible]) {
			_ShowHitmarker(playerid, weaponid, hittype, color, .bodypart = -1);
		}
		else if(Hitmarker[playerid][h_Visible]) {

			if(Hitmarker[playerid][h_HitType] != hittype && hittype >= BULLET_HIT_TYPE_PLAYER && hittype <= BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitTypeEnabled][hittype]) {
				// * Update the hitmarker color if the hittype has changed
				
				Hitmarker[playerid][h_BodyPart] = -1;
				Hitmarker[playerid][h_HitType] = hittype;
				Hitmarker[playerid][h_Color] = color;

				PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_Color]);
				PlayerTextDrawShow(playerid, Hitmarker[playerid][h_TextDraw]);
			}
			else if(Hitmarker[playerid][h_HitType] == hittype && hittype == BULLET_HIT_TYPE_VEHICLE && Hitmarker[playerid][h_HitTypeEnabled][BULLET_HIT_TYPE_VEHICLE]) {
				
				Hitmarker[playerid][h_ShowTime] = GetTickCount() + HITMARKER_VISIBLE_TIME;

				if(Hitmarker[playerid][h_Color] != Hitmarker[playerid][h_HitColors][HITMARKER_COLOR_VEHICLE]) {
					Hitmarker[playerid][h_Color] = Hitmarker[playerid][h_HitColors][HITMARKER_COLOR_VEHICLE];

					PlayerTextDrawColor(playerid, Hitmarker[playerid][h_TextDraw], Hitmarker[playerid][h_Color]);
					PlayerTextDrawShow(playerid, Hitmarker[playerid][h_TextDraw]);
				}
			}
			else if(Hitmarker[playerid][h_HitType] != hittype && !Hitmarker[playerid][h_Killed]) {
				_HideHitmarker(playerid);
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
	Hitmarker[playerid][h_X] = 332.5;
	Hitmarker[playerid][h_Y] = 172.5;
	Hitmarker[playerid][h_SizeX] = 0.33;
	Hitmarker[playerid][h_SizeY] = 0.7;

	Hitmarker[playerid][h_CenterX] = 310.5; 
	Hitmarker[playerid][h_CenterY] = 214.0;
	Hitmarker[playerid][h_CenterSizeX] = 0.46; 
	Hitmarker[playerid][h_CenterSizeY] = 1.0;

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
    if(IsHitmarkerEnabled(playerid)) {
		HitmarkerDisable(playerid);
	}

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
