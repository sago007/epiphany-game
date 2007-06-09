/***************************************************************************
                          sprite.cpp  -  description
                             -------------------
    begin                : Sat Sep 22 2001
    copyright            : (C) 2001 by Giuseppe D'Aqu�
    email                : kumber@tiscalinet.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "dephine.h"
#include "sprite.h"
//#include <cmath>

Sprite::Sprite(Surface* surface)
{

	m_surface=surface;
	
	m_pos_x=0;
	
	m_pos_y=0;
	
	m_move_to_pos_x=0;
	
	m_move_to_pos_y=0;
	
	m_initialized=true;
	
	m_curr_frame=0;
	
	m_speed=1;
	
	m_state = SP_STOP;
	
}

Sprite::Sprite(const Sprite& sprite)
{

	//DEBOUT("Entering Sprite cpyctor...\n");

//	CL_Surface temp=*(sprite.m_surface);

//	m_surface=new CL_Surface(temp);

	m_surface=sprite.m_surface;
	
	m_pos_x=sprite.m_pos_x;
	
	m_pos_y=sprite.m_pos_y;
	
	m_move_to_pos_x=sprite.m_move_to_pos_x;
	
	m_move_to_pos_y=sprite.m_move_to_pos_y;
	
	m_initialized=true;
	
	m_curr_frame=sprite.m_curr_frame;

	m_speed=sprite.m_speed;
	
	m_state = sprite.m_state;
	
}
/*
Sprite& Sprite::operator=(const Sprite& sprite)
{

	CL_Surface temp=*(sprite.m_surface);

	m_surface=new CL_Surface(temp);
	
	m_pos_x=sprite.m_pos_x;
	
	m_pos_y=sprite.m_pos_y;
	
	m_move_to_pos_x=sprite.m_move_to_pos_x;
	
	m_move_to_pos_y=sprite.m_move_to_pos_y;
	
	m_initialized=true;
	
	return (*this);
	
}*/

void Sprite::init(Surface* surf)
{

	m_surface=surf;
	
	m_pos_x=0;
	
	m_pos_y=0;
	
	m_move_to_pos_x=0;
	
	m_move_to_pos_y=0;

	m_initialized=true;
	
	m_state = SP_STOP;
	
}
	
Sprite::~Sprite()
{
	
	
}
void Sprite::put_screen(int x, int y, unsigned int size_x, unsigned int size_y, unsigned int frame_num)
{
	m_surface->put_screen(x, y, (int)size_x, (int)size_y, (int)frame_num);
}

void Sprite::put_screen(int x, int y, unsigned int size_x, unsigned int size_y)
{
	m_surface->put_screen(x, y, (int)size_x, (int)size_y, m_curr_frame+m_state);
}

/*
CL_Surface* Sprite::operator->()
{
	//qui dovrebbe ritornare il frame di m_surface
	//corrispondente a m_curr_frame
	return m_surface;
}
*/
 /*
unsigned int Sprite::get_pos_x()
{
	return m_pos_x;
}

unsigned int Sprite::get_pos_y()
{
	return m_pos_y;
}
*/
void Sprite::set_pos_x(unsigned int pos_x)
{
	m_pos_x=pos_x;
	m_move_to_pos_x=pos_x;
}

void Sprite::set_pos_y(unsigned int pos_y)
{
	m_pos_y=pos_y;
	m_move_to_pos_y=pos_y;
}

void Sprite::set_curr_frame(int frame)
{
	//FIXME: check should be on mumber of sprite frames
	if(frame >= Epiconfig::instance()->get_max_anim_drawn())
	{
		m_curr_frame = 0;
	}
	else
	{
		m_curr_frame=frame;
	}
}

void Sprite::set_speed(unsigned int speed)
{
	m_speed=speed;
}

void Sprite::move(unsigned int n_pixel)
{
	
	n_pixel*=m_speed;
	if(m_pos_x<m_move_to_pos_x)
	{
		if(m_pos_x+n_pixel>m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x+=n_pixel;
		}
	}
	else if(m_pos_x>m_move_to_pos_x)
	{
		if(m_pos_x-n_pixel<m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x-=n_pixel;
		}
	}

	if(m_pos_y<m_move_to_pos_y)
	{
		if(m_pos_y+n_pixel>m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y+=n_pixel;
		}
	}
	else if(m_pos_y>m_move_to_pos_y)
	{
		if(m_pos_y-n_pixel<m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y-=n_pixel;
		}
	}



}

void Sprite::move()
{
	
	int n_pixel = k_sprite_size/Epiconfig::instance()->get_max_anim_drawn();
	
	n_pixel*=m_speed;
	if(m_pos_x<m_move_to_pos_x)
	{
		if(m_pos_x+n_pixel>m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x+=n_pixel;
		}
	}
	else if(m_pos_x>m_move_to_pos_x)
	{
		if(m_pos_x-n_pixel<m_move_to_pos_x)
		{
			m_pos_x=m_move_to_pos_x;
		}
		else
		{
			m_pos_x-=n_pixel;
		}
	}

	if(m_pos_y<m_move_to_pos_y)
	{
		if(m_pos_y+n_pixel>m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y+=n_pixel;
		}
	}
	else if(m_pos_y>m_move_to_pos_y)
	{
		if(m_pos_y-n_pixel<m_move_to_pos_y)
		{
			m_pos_y=m_move_to_pos_y;
		}
		else
		{
			m_pos_y-=n_pixel;
		}
	}



}

int Sprite::get_frame_number()
{

	//return m_curr_frame+m_state;
	return m_curr_frame;
}

void Sprite::set_state(Anim_Type state)
{
	m_state=state;
}

void Sprite::move_to_pos(unsigned int x, unsigned int y)
{
	m_move_to_pos_x=x;
	m_move_to_pos_y=y;
}


void Sprite::move_to_pos_x(unsigned int x)
{
	m_move_to_pos_x=x;
}

void Sprite::move_to_pos_y(unsigned int y)
{
	m_move_to_pos_y=y;
}


void Sprite::update_frame()
{
	set_curr_frame(m_curr_frame+1);
}
