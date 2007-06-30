#include "dephine.h"
#include <SDL/SDL_mixer.h>
#include "music_manager.h"
#include "resource_factory.h"

void Music_Manager::init()
{
	//FIXME: we should auto-resize the vector
	m_musics.resize(25);
	
	load_musics();
	
	this->set_volume(Epiconfig::instance()->get_volume_music());
}


void Music_Manager::load_musics()
{

	Resource_Factory* res_factory=Resource_Factory::instance();

	std::string res_path(res_factory->get_resource_path());

	res_path+= "/sfx/";

	//FIXME should check the existence of music files
	m_musics[MUS_MENU]=Mix_LoadMUS((res_path+"epiphany_menu.ogg").c_str());

	m_musics[MUS_CREDITS]=Mix_LoadMUS((res_path+"emerald_eat.wav").c_str());

	m_musics[MUS_GAME]=Mix_LoadMUS((res_path+"epiphany_game.ogg").c_str());

	m_musics[MUS_READY]=Mix_LoadMUS((res_path+"epiphany_ready.ogg").c_str());

}

void Music_Manager::deinit()
{
	Mix_FreeMusic(m_musics[MUS_MENU]);
	Mix_FreeMusic(m_musics[MUS_CREDITS]);
	Mix_FreeMusic(m_musics[MUS_GAME]);
	Mix_FreeMusic(m_musics[MUS_READY]);
	Epiconfig::instance()->set_volume_music(this->get_volume());
}

Mix_Music* Music_Manager::get_music(Music_Type music)
{
	//FIXME: it should assert the existence of sample
	return m_musics[music];
	
}




void Music_Manager::play(Music_Type type)
{
	Mix_Music* music = get_music(type);
	
	if(Mix_PlayMusic(music, -1)==-1) {
    	DEBWARN("Mix_PlayMusic: "<< Mix_GetError()<<"\n");
	}
}


Uint32 Music_Manager::get_max_volume()
{
	return MIX_MAX_VOLUME/16;
}




void Music_Manager::set_volume(Uint32 value)
{
	Mix_VolumeMusic(value*16);
}




Uint32 Music_Manager::get_volume()
{
	return Mix_VolumeMusic(-1)/16;
}




Music_Manager* Music_Manager::_instance = 0;

Music_Manager* Music_Manager::instance()
{
	if(_instance==0)
	{
		_instance=new Music_Manager();
		_instance->init();
	}
	return _instance;
}
