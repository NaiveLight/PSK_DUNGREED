#pragma once

enum TEXTYPE { TEX_SINGLE, TEX_MULTI };
enum SCENEID { SCENE_LOGO, SCENE_TITLE, SCENE_TOWN, SCENE_ROOM1, SCENE_ROOM2, SCENE_ROOM3, SCENE_BOSSROOM, SCENE_END };
enum OBJID { OBJ_BACKGROUND, OBJ_LAYER, OBJ_TILEMAP, OBJ_MAPOBJ, OBJ_ACTOR, OBJ_MONSTER, OBJ_PLAYER, OBJ_PATTACK, OBJ_MATTACK, OBJ_BULLET, OBJ_EFFECT, OBJ_UI, OBJ_CURSOR, OBJ_END };
enum COLLTILEID { COLL_DEFAULT, COLL_UPDIG, COLL_DOWNDIG, COLL_LINE, COLL_RECT, COLL_DUNGEON, COLL_ROOM};
enum BUTTONID {BT_TSTART, BT_TOPTION, BT_TEXIT, BT_GOPTION, BT_GEXIT, BT_UEXIT, BT_END};
enum WEAPONID {WP_HAND, WP_SWORD, WP_HALBERD};
enum DATAID { PLAYER_DATA, PLAYER_PDATA, PLAYER_MATRIX, BOSS_DATA };
enum BULLETID { BULLET_BANSHEE, BULLET_BELIAL_HAND, BULLET_BELIAL_HEAD };