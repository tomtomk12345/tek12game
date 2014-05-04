#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp();
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

private:
  SDL_Surface           * surface;
  bool                    is_running;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > carrots;
  list<shared_ptr<SFAsset> > foxs;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > walls2;
  list<shared_ptr<SFAsset> > vertWalls;
  list<shared_ptr<SFAsset> > vertWalls2;
  list<shared_ptr<SFAsset> > players;
  list<shared_ptr<SFAsset> > foxs2;
  list<shared_ptr<SFAsset> > foxs3;
  list<shared_ptr<SFAsset> > foxs4;
  list<shared_ptr<SFAsset> > wins;

  SFError OnInit();
};
#endif
