/*

  Our Window Functions

 */

#include "Frame.h"
#include "Window.h"

#include "SDL/SDL.h"

#include <vector>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 748;
const int SCREEN_BPP = 32;





Window::Window(){

  // Set up the screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );

  if( screen == NULL ){
    windowOK = false;
    return;
  }
  else{
    windowOK = true;
  }
  
  SDL_WM_SetCaption( "The ASCII Project - Client - 0.0.1f", NULL);

  windowed = true;
  //  eventQueue = nullptr;
  
}


void Window::Toggle_Fullscreen(){
  
  //If the screen is windowed
  if( windowed == true )
    {
      //Set the screen to fullscreen
      screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
      
      //If there's an error
      if( screen == NULL )
        {
          windowOK = false;
          return;
        }
      
      //Set the window state flag
      windowed = false;
    }
  //If the screen is fullscreen
  else if( windowed == false )
    {
      //Window the screen
      screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
      
      //If there's an error
      if( screen == NULL )
        {
          windowOK = false;
          return;
        }
      
      //Set the window state flag
      windowed = true;
    }
}


void Window::Clear_Screen(){

  uint32_t black = SDL_MapRGB( screen->format, 0, 0, 0);
  SDL_FillRect( screen, NULL, black);

}




void Window::Handle_Events(SDL_Event event){

//If there's something wrong with the window
    if( windowOK == false )
    {
        return;    
    }
    
    //If the window resized
    if( event.type == SDL_VIDEORESIZE )
    {
        //Resize the screen
        screen = SDL_SetVideoMode( event.resize.w, event.resize.h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
        
        //If there's an error
        if( screen == NULL )
        {
            windowOK = false;
            return;
        }
    }

 //If enter was pressed
    else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) && ( event.key.keysym.mod & KMOD_ALT ))
    {
        //Turn fullscreen on/off
        Toggle_Fullscreen();
    }

    /*
 //If the window focus changed
    else if( event.type == SDL_ACTIVEEVENT )
    {
        //If the window was iconified or restored
        if( event.active.state & SDL_APPACTIVE )
        {
            //If the application is no longer active
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Iconified", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }


//If something happened to the keyboard focus
        else if( event.active.state & SDL_APPINPUTFOCUS )
        {
            //If the application lost keyboard focus
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Keyboard focus lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the mouse focus
        else if( event.active.state & SDL_APPMOUSEFOCUS )
        {
            //If the application lost mouse focus
            if( event.active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Mouse Focus Lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        } */
//If the window's screen has been altered
    else if( event.type == SDL_VIDEOEXPOSE )
    {
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            //If there's an error
            windowOK = false;
            return;
        }
    }
}


void Window::Add_To_FrameList(Frame *src){

  frameList.push_back(src);

}


void Window::Draw_Frames(){

  for( int i = 0; i < frameList.size(); i++){

    // This doesn't actually make the Frame process the event
    // It only tells the Frame that it now has an Event to process
    if( frameList.at(i)->Check_Focus() ){
      //SDL_Event tmpEvent = *eventQueue;
      frameList.at(i)->Handle_Event( eventQueue );
      //      delete eventQueue;
    }
    frameList.at(i)->Render_Widgets();
    
    if( frameList.at(i)->drawThisFrame ){

      SDL_Rect destination;

      destination.x = frameList.at(i)->posX;
      destination.y = frameList.at(i)->posY;

      destination.w = frameList.at(i)->width;
      destination.h = frameList.at(i)->height;

      SDL_BlitSurface( frameList.at(i)->sdlScreen, NULL, screen, &destination);      

    }

    if( frameList.at(i)->removeThisFrame ){
      frameList.erase(frameList.begin()+i);
      return;
    }
    
    if( frameList.at(i)->Get_FrameList_Index() != i ){
      frameList.at(i)->Set_FrameList_Index( i );
    }
      
    // We check if we need to drop this frame, if not then we validate
    // the index and if this frame is at the top of the 
    
    if( (frameList.at(i)->Get_FrameList_Index() == (frameList.size() - 1)) && ( !frameList.at(i)->Check_Focus() ) ){
      // We move the frame to the end of the frameList vector and set
      // Focus to 'true' so that the frame in question has 
      frameList.at(i)->Set_Focus( true );
      frameList.push_back(frameList.at(i));
      frameList.erase(frameList.begin()+i);
    }
      else if( frameList.at(i)->Get_FrameList_Index() != (frameList.size() -1) ){
      frameList.at(i)->Set_Focus( false );
    }
    
  }

}



bool Window::Error()
{
    return !windowOK;
}



void Window::Add_To_Event_Queue( SDL_Event event ){

  eventQueue = event;

}
