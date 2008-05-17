/***************************************************************************
                          entity_peperon.cpp  -  description
                             -------------------
    begin                : Tue Apr 23 2002
    copyright            : (C) 2002 by Giuseppe D'Aqui'
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License, Version 2, as published by  *
 *   the Free Software Foundation.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dephine.h"
#include "entity.h"
#include "entity_monster.h"
#include "entity_manager.h"
#include "entity_tomato.h"
#include "entity_player.h"

Entity_Tomato::Entity_Tomato(Level* level, Uint32 x, Uint32 y, Direction direction)
{
	current_level=level;
	m_position_x=x;
	m_position_y=y;
	m_type=PEPERON;
	Surface_Manager* surf_man = Surface_Manager::instance();
	m_sprite.init(surf_man->get_surface(Surface_Manager::SRF_TOMATO));
	m_sprite.set_state(SP_STOP);
	m_exists=true;
	m_is_exploding=false;
	m_direction=direction;

}
	
void Entity_Tomato::check_and_do()
{
	if(m_just_checked==true)
	{

		
		return;
	}
	
	if(m_is_exploding==true)
	{

		explode_all_around();	
		return;
	}
	
	Entity_Handle up_entity_id=current_level->get_entity(m_position_x, m_position_y, UP);	
	Entity_Handle right_entity_id=current_level->get_entity(m_position_x, m_position_y, RIGHT);
	Entity_Handle down_entity_id=current_level->get_entity(m_position_x, m_position_y, DOWN);
	Entity_Handle left_entity_id=current_level->get_entity(m_position_x, m_position_y, LEFT);
	
	if(((up_entity_id!=0)&&(Entity_Manager::instance()->get_entity(up_entity_id)->get_type()==PLAYER))||
		((right_entity_id!=0)&&(Entity_Manager::instance()->get_entity(right_entity_id)->get_type()==PLAYER))||
		((down_entity_id!=0)&&(Entity_Manager::instance()->get_entity(down_entity_id)->get_type()==PLAYER))||
		((left_entity_id!=0)&&(Entity_Manager::instance()->get_entity(left_entity_id)->get_type()==PLAYER)))
	{
		kill();
		current_level->do_player_stop();
		return;
	}
	
	switch(m_direction)
	{
	case UP:
		if(right_entity_id!=0)
		{
			if(up_entity_id!=0)
			{
				m_direction=LEFT;
			}

		}
		else
		{
			m_direction=RIGHT;
		}
		break;
		
	case RIGHT:
		if(down_entity_id!=0)
		{
			if(right_entity_id!=0)
			{
				m_direction=UP;
			}

		}
		else
		{
			m_direction=DOWN;
		}
		break;
		
	case DOWN:
		if(left_entity_id!=0)
		{
			if(down_entity_id!=0)
			{
				m_direction=RIGHT;
			}

		}
		else
		{
			m_direction=LEFT;
		}
		break;
		
	case LEFT:
		if(up_entity_id!=0)
		{
			if(left_entity_id!=0)
			{
				m_direction=DOWN;
			}

		}
		else
		{
			m_direction=UP;
		}
		break;
		
	default:
		m_sprite.set_state(SP_STOP);
	}
	if(current_level->get_entity(m_position_x, m_position_y, m_direction)==0)
	{

		Sample_Manager::instance()->play(SFX_MONSTER_MOVE);

		move(m_direction);

	}
		
	m_just_checked=true;
}
	
bool Entity_Tomato::hit_from_up(Entity_Handle smasher)
{
	if(Entity_Manager::instance()->get_entity(smasher)->get_type()==BOULDER)
	{
		kill();
		
	}
	return false;

}
	


void Entity_Tomato::kill()
{

	current_level->explode(m_position_x, m_position_y, SAPPHIRE);

	
}	

void Entity_Tomato::explode_all_around()
{
	Entity::kill();
	current_level->explode(m_position_x-1,m_position_y-1, EMERALD);
	current_level->explode(m_position_x,m_position_y-1, EMERALD);
	current_level->explode(m_position_x+1,m_position_y-1, EMERALD);
	current_level->explode(m_position_x-1,m_position_y, EMERALD);

	current_level->explode(m_position_x+1,m_position_y, EMERALD);
	current_level->explode(m_position_x-1,m_position_y+1, EMERALD);
	current_level->explode(m_position_x,m_position_y+1, EMERALD);
	current_level->explode(m_position_x+1,m_position_y+1, EMERALD);
}


bool Entity_Tomato::explode()
{

	if(m_just_checked==true)
	{
		m_is_exploding=true;
	}
	else
	{
		m_is_exploding=true;
		m_just_checked=true;
	}
	

	return true;
}
