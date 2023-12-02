#pragma once

enum EntityType
{
    Player_Entity,
    AI_Entity,
    Weapon_Entity,
    Projectile_Entity,
    Objectif_Entity,
    Wall_Entity,
    None_Entity,
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