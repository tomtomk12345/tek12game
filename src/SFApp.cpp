#include "SFApp.h"

SFApp::SFApp() : is_running(true) {

    // Box/surface settings
    surface = SDL_GetVideoSurface();
    app_box = make_shared<SFBoundingBox>(Vector2(surface->w/2, surface->h/2), surface->w/2, surface->h/2);

    // Player settings & position
    player  = make_shared<SFAsset>(SFASSET_PLAYER);
    auto player_pos = Point2(surface->w/2, 270.0f);
    player->SetPosition(player_pos);
    players.push_back(player);

    // bottom horizontal wall settings
    auto wall = make_shared<SFAsset>(SFASSET_WALL);
    auto wall_pos = Point2((surface->w/2), 20.0f);
    wall->SetPosition(wall_pos);
    walls.push_back(wall);

    // top horizontal wall settings
    auto wall2 = make_shared<SFAsset>(SFASSET_WALL2);
    auto wall2_pos = Point2((surface->w/2), 487.0f);
    wall2->SetPosition(wall2_pos);
    walls2.push_back(wall2);

    // right hand side vertical wall settings
    auto vertWall = make_shared<SFAsset>(SFASSET_VERTWALL);
    auto vertWall_pos = Point2((surface->w/1.010), 720.0f);
    vertWall->SetPosition(vertWall_pos);
    vertWalls.push_back(vertWall);

    // left hand side vertical wall settings
    auto vertWall2 = make_shared<SFAsset>(SFASSET_VERTWALL2);
    auto vertWall2_pos = Point2((surface->w/90), 720.0f);
    vertWall2->SetPosition(vertWall2_pos);
    vertWalls2.push_back(vertWall2);

    // amount of edible items on the screen
    const int number_of_carrots = 12;

    //place an edible at width/number_of_c * i
    for(int i=0; i<number_of_carrots; i++)
    {
    auto carrot = make_shared<SFAsset>(SFASSET_CARROT);
    auto carrot_pos   = Point2((surface->w/number_of_carrots) * i, 450.0f);
    carrot->SetPosition(carrot_pos);
    carrots.push_back(carrot);
    }

    //place an edible at width/number_of_c * i
    for(int i=0; i<number_of_carrots; i++)
    {
    auto carrot = make_shared<SFAsset>(SFASSET_CARROT);
    auto carrot_pos   = Point2((surface->w/number_of_carrots) * i, 360.0f);
   carrot->SetPosition(carrot_pos);
    carrots.push_back(carrot);
    }

    //place an edible at width/number_of_c * i
    for(int i=0; i<number_of_carrots; i++)
    {
    auto carrot = make_shared<SFAsset>(SFASSET_CARROT);
    auto carrot_pos   = Point2((surface->w/number_of_carrots) * i, 270.0f);
    carrot->SetPosition(carrot_pos);
    carrots.push_back(carrot);
    }

    //place an edible at width/number_of_c * i
    for(int i=0; i<number_of_carrots; i++)
    {
    auto carrot = make_shared<SFAsset>(SFASSET_CARROT);
    auto carrot_pos   = Point2((surface->w/number_of_carrots) * i, 180.0f);
    carrot->SetPosition(carrot_pos);
    carrots.push_back(carrot);
    }

    //place an edible at width/number_of_c * i
    for(int i=0; i<number_of_carrots; i++)
    {
    auto carrot = make_shared<SFAsset>(SFASSET_CARROT);
    auto carrot_pos   = Point2((surface->w/number_of_carrots) * i, 90.0f);
    carrot->SetPosition(carrot_pos);
    carrots.push_back(carrot);
    }

    // enemy one settings
    auto fox = make_shared<SFAsset>(SFASSET_FOX);
    auto fox_pos  = Point2((surface->w/1.1), 140);
    fox->SetPosition(fox_pos);
    foxs.push_back(fox);

    // enemy two settings
    auto fox2 = make_shared<SFAsset>(SFASSET_FOX);
    auto fox2_pos  = Point2((surface->w/12), 230);
    fox2->SetPosition(fox2_pos);
    foxs2.push_back(fox2);

    // enemy three settings
    auto fox3 = make_shared<SFAsset>(SFASSET_FOX);
    auto fox3_pos  = Point2((surface->w/1.1), 300);
    fox3->SetPosition(fox3_pos);
    foxs3.push_back(fox3);

    // enemy four settings
    auto fox4 = make_shared<SFAsset>(SFASSET_FOX);
    auto fox4_pos  = Point2((surface->w/12), 400);
    fox4->SetPosition(fox4_pos);
    foxs4.push_back(fox4);

    auto win = make_shared<SFAsset>(SFASSET_YOUWIN);
    auto win_pos = Point2((surface->w/2), 700);
    win->SetPosition(win_pos);
    wins.push_back(win);
}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;

  // player direction settings
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_UP:
    player->GoUp();
    break;
  case SFEVENT_PLAYER_DOWN:
    player->GoDown();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {

//detect collision between player and edible.
for (auto pl: players)
{
    for (auto a: carrots)
    {
        if (pl->CollidesWith(a))
        {
            pl->HandleCollision();
            a->HandleCollision();
        }
    }
}

// detect collision between player and enemy
for (auto c: foxs)
{
    for (auto pl: players)
    {
        if (c->CollidesWith(pl))
        {
            c->HandleCollision();
            pl->HandleCollision();
        }
    }
}

//detect collision between player and wall
for (auto pl: players)
{
    for (auto vw: vertWalls)
    {
        if (pl > vw)
        {
            pl->GoWest();
        }
    }
}

  // settings to remove dead foxs
  list<shared_ptr<SFAsset>> tmp2;
  for(auto c : foxs) {
    if(c->IsAlive()) {
      tmp2.push_back(c);
    }
  }
  foxs.clear();
  foxs = list<shared_ptr<SFAsset>>(tmp2);

  // wall thing.
  list<shared_ptr<SFAsset>> tmp3;
  for(auto vw: vertWalls)
  {
      if(vw->IsAlive())
      {
          tmp3.push_back(vw);
      }
  }
  vertWalls.clear();
  vertWalls = list<shared_ptr<SFAsset>>(tmp3);

  // remove dead carrots
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : carrots) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  carrots.clear();
  carrots = list<shared_ptr<SFAsset>>(tmp);
}

void SFApp::OnRender() {

  // background settings
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 50, 164, 50) );

  // render the player on the screen
  for (auto pl: players)
  {
      if(pl->IsAlive())
      {
          pl->OnRender(surface);
      }
  }

  for(auto a: carrots) {
    if(a->IsAlive()) {a->OnRender(surface);}
  }

  for (auto c: foxs)
  {
      if (c->IsAlive())
      {
          c->OnRender(surface);
      }
  }

  for (auto wi: wins)
  {
      if (wi->IsAlive())
      {
      }
  }


  for (auto w: walls){
    w->OnRender(surface);
  }

  for (auto w2: walls2){
    w2->OnRender(surface);
  }

  for (auto vw: vertWalls)
  {
      if(vw->IsAlive())
      {
          vw->OnRender(surface);
      }
  }

  for (auto vw2: vertWalls2)
  {
    vw2->OnRender(surface);
  }

  for (auto c2: foxs2)
  {
      c2->OnRender(surface);
  }

    for (auto c3: foxs3)
  {
      c3->OnRender(surface);
  }

    for (auto c4: foxs4)
  {
      c4->OnRender(surface);
  }

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}
