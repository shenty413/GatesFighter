#include "game.h"
#include "fssimplewindow.h"
#include "player.h"
#include <time.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"

YsSoundPlayer musicplayer( YsSoundPlayer::SoundData *punch, YsSoundPlayer::SoundData *bleeding,
                          YsSoundPlayer::SoundData *moaning, YsSoundPlayer::SoundData *running)
{
    /* An instance of YsSoundPlayer */
    YsSoundPlayer player;
   
    
    /* The sound player object must be made current and started before playing a sound data. */
    /* Make sure to do this after opening a Window. */
    player.MakeCurrent();
    player.Start();
    /* The point is you first need to add a folder reference, not a group, to your project before adding to
     the copy files phase. */
    FsChangeToProgramDir();
    
    
    // Use LoadWav function for loading a .WAV file to the variable.
    // Just in case you ended up copying datafiles directory instead of individual files,
    
    /* load running sound */
    if(YSOK != running->LoadWav("running.wav") &&
       YSOK != running->LoadWav("datafiles/running.wav"))
    {
        printf("Error!  Cannot load moaning.wav!\n");
    }
    /* load moaning sound */
    if(YSOK!= moaning->LoadWav("moaning.wav") &&
       YSOK!= moaning->LoadWav("datafiles/moaning.wav"))
    {
        printf("Error!  Cannot load bleeding.wav!\n");
    }
    /* load punch sound */
    if(YSOK!= punch->LoadWav("punch.wav") &&
       YSOK!= punch->LoadWav("datafiles/punch.wav"))
    {
        printf("Error!  Cannot load bleeding.wav!\n");
    }
    return player;
}

void Game::SetCharacter(int pn1, int pn2){
    p1.SetCharacter(pn1);
    p2.SetCharacter(pn2);
}

const bool Game::isExit(void) const {
    return exit;
};

const bool Game::isTimeout(void) const {
    return timeout;
};

const bool Game::isKo(void) const {
    return ko;
};

void Game::setExit(void) {
    exit = true;
}

void Game::setTimeout(void) {
    timeout = true;
}

void Game::setKo(void) {
    ko = true;
}

void Game::Run(){
		int key = FsInkey();
		switch (key) {
		case FSKEY_ESC: // exit the game 
			setExit();
			termination = 1;
			break;

			// player 2 moves 
		case FSKEY_W: // jump 
			// if not jumping, jump 
			if (p2.IsJumping() == 0)
				p2.InitializeJumping();
			break;
		case FSKEY_A: // move left 
			// if punching, cannot move  
			break;
		case FSKEY_S: // move right 
			// if punching, cannot move  
			break;
		case FSKEY_D: // punch 
			break;

			// player 2 moves 
		case FSKEY_I: // jump 
			// if not jumping, jump
			break;
		case FSKEY_J: // move left 
			// if punching, cannot move  
			break;
		case FSKEY_K: // move right 
			// if punching, cannot move  
			break;
		case FSKEY_L: // punch 
			// if not punching, punch 
			if (p2.IsPunching())
			{
				punch_timer = 0;
			}
			break;
		default:
			break;
		}
		// player 1 punching 
		if (p1.IsPunching()) 
		{				

			p1.Punch();
			if (p1.IfPunchHit(p2)) 
			{
			
			}
			if (p1.CheckFinishPunching())
			{

			}
		}
		// player 1 jumping 
		if (p1.IsJumping()) 
		{
			
		}
		// player 2 jumping 
		if (p2.IsPunching()) 
		{
		
		}
		// player 2 punching 
		if (p2.IsJumping()) 
		{
		
		}

		// count time, check if time runs out 
		int current_time = (int)time(NULL);
		if (current_time - timer >= 20)
			termination = 1;
	}
                player.Stop(running);
                player.PlayOneShot(running);
                break;
            case FSKEY_J: // move left
                // if punching, cannot move
                /* play move sound */
                player.Stop(running);
                player.PlayOneShot(running);
                break;
            case FSKEY_K: // move right
                // if punching, cannot move
                /* play move sound */
                player.Stop(running);
                player.PlayOneShot(running);
                break;
            case FSKEY_L: // punch
                // if not punching, punch
                /* if punch, play punch sound */
                player.Stop(punch);
                player.PlayOneShot(punch);
                if (p2.IsPunching())
                {
                    punch_timer = 0;
                }
                break;
            default:
                break;
        }
        // player 1 punching
        if (p1.IsPunching())
        {
            
            p1.Punch();
            if (p1.IfPunchHit(p2))
            {
                /* if hit, play moaning sound */
                player.Stop(moaning);
                player.PlayOneShot(moaning);
            }
            if (p1.CheckFinishPunching())
            {
                /* if punch, play punch sound */
                player.Stop(punch);
                player.PlayOneShot(punch);
                
            }
        }
        // player 1 jumping
        if (p1.IsJumping())
        {
            /* play move sound */
            /* play move sound */
            player.Stop(running);
            player.PlayOneShot(running);
        }
    printf("p1 attack: %d\n",p1.getAttack());
    printf("p2 attack: %d\n",p2.getAttack());
}
