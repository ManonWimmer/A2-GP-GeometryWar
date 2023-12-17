#pragma once

enum EntityType
{
    Player_Entity,
    AI_Entity,
    Weapon_Entity,
    Projectile_Entity,
    Objectif_Entity,
    Building_Entity,
    None_Entity,
    Light_Entity,
    Audio_Entity,
};

enum Faction
{
    PlayerFaction,
    EnemiesFaction,
    None_Faction,
};

enum CollisionType
{
    Circle,
    Rectangle,
    None_CollisionType,
};