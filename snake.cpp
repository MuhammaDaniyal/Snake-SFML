#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

const int resolutionX = 960;            //Initializing rows pixels
const int resolutionY = 960;            //Initializing columns pixels
const int boxPixelsX = 32;              //Boxes on rows
const int boxPixelsY = 32;              //Boxes on columns
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

enum direction
{
    Down,
    Left,
    Right,
    Up
};

//dir is  and size is its 
int dir,                //direction of the snake
    size=4,             //initial size of the snake
    PosSnake[100][2],   //Letting that there are 100 beads of the snake and it will store the positions of that bead
    Posfruit[2];        //Array for fruits position
    

int main()
{

    //It will render window with follwing reolutions   with title ↓↓↓↓↓↓↓↓↓   This ensures close window option and title baar
    RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Snake", sf::Style::Close | sf::Style::Titlebar);
    window.setSize(sf::Vector2u(640, 640));                 //It will set window size to 640 sqaure pixels
    window.setPosition(sf::Vector2i(700, 0));

///////////////////////////////////////////////////////////////
//                  Game Objects initialization              //
///////////////////////////////////////////////////////////////

    //Initializing heads
    Texture LheadTexture;                                                   //Texture for left side head
	LheadTexture.loadFromFile("images/head_left.png");                      //Loading texture
	
    
    Sprite LHeadCent(LheadTexture);                                         //making a sprite with left texture
	LHeadCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));   //cutting single bead out of it

    Texture RheadTexture;
	RheadTexture.loadFromFile("images/head_right.png");
	Sprite RHeadCent(RheadTexture);
	RHeadCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

    Texture UpheadTexture;
	UpheadTexture.loadFromFile("images/head_up.png");
	Sprite UpHeadCent(UpheadTexture);
	UpHeadCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

    Texture DownheadTexture;
	DownheadTexture.loadFromFile("images/head_down.png");
	Sprite DownHeadCent(DownheadTexture);
	DownHeadCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

    //Initializing body
	Texture RBodyTexture;
	RBodyTexture.loadFromFile("images/body_right.png");
	Sprite RBodyCent(RBodyTexture);
	RBodyCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

	Texture verBodyTexture;
	verBodyTexture.loadFromFile("images/body_ver.png");
	Sprite verticalBodyCent(verBodyTexture);
	verticalBodyCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

	Texture LBodyTexture;
	LBodyTexture.loadFromFile("images/body_left.png");
	Sprite LBodyCent(LBodyTexture);
	LBodyCent.setTextureRect(IntRect( 0 , 0 , boxPixelsX , boxPixelsY ));

    Sprite Head = DownHeadCent;             //MAking another single sprite for head just for ease else are 4 sprites
    Sprite Body = verticalBodyCent;         //MAking another single sprite for body just for ease else are 4 sprites

    Color FILL = Color::Red;                //This is for text colours to remain synced

	Texture fruitT;         //Texture for fruit
	fruitT.loadFromFile("images/f_g.png");
	Sprite fruit1(fruitT);
	fruit1.setTextureRect(IntRect( 33 , 26 , 53 , 48 ));

	Font font;								//Initializing font
	// font.loadFromFile("Fonts/Grenze-Black.ttf");			
	// font.loadFromFile("Fonts/Poppins-Black.ttf");			
	font.loadFromFile("Fonts/Amatic-Bold.ttf");			
	// font.loadFromFile("Fonts/Roboto-Black.ttf");			
	// font.loadFromFile("Fonts/Amatic-Bold.ttf");			

    int score=0;
   
    Text Score;                 //Text for score while playing
    Score.setFont(font);
	Score.setCharacterSize(56);
	Score.setFillColor(Color::Red);
	Score.setString( "Score " + to_string(score) );
	Score.setPosition(2,2);

    Text ScoreMain;             //Text of score that will come after game over
    ScoreMain.setFont(font);
	ScoreMain.setCharacterSize(70);
	ScoreMain.setFillColor(Color::Red);
	ScoreMain.setString( "Score " + to_string(score) );
	ScoreMain.setPosition(450,550);

    Text GameOver;              //TExt of game over
    GameOver.setFont(font);
	GameOver.setCharacterSize(200);
	GameOver.setFillColor(Color::Red);
	GameOver.setString( "Game Over");
	GameOver.setPosition(250,250);

///////////////////////////////////////////////////////////////
//                  initializating background                //
///////////////////////////////////////////////////////////////


	// Initializing Background.
    float opacity=0.3;
    Sprite backgroundSprite;

	sf::Texture backgroundTextureMain;
	sf::Sprite backgroundSpriteMain;
	backgroundTextureMain.loadFromFile("images/BackGrounds/lava.png");
	backgroundSpriteMain.setTexture(backgroundTextureMain);
	backgroundSpriteMain.setColor(sf::Color(255, 255, 255, 255 *opacity)); // Reduces Opacity of the background

	sf::Texture backgroundTexture1;
	sf::Sprite backgroundSprite1;
	backgroundTexture1.loadFromFile("images/BackGrounds/w1_r.png");
	backgroundSprite1.setTexture(backgroundTexture1);
	backgroundSprite1.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture2;
	sf::Sprite backgroundSprite2;
	backgroundTexture2.loadFromFile("images/BackGrounds/w1_b.jpg");
	backgroundSprite2.setTexture(backgroundTexture2);
	backgroundSprite2.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture3;
	sf::Sprite backgroundSprite3;
	backgroundTexture3.loadFromFile("images/BackGrounds/w1_g.jpg");
	backgroundSprite3.setTexture(backgroundTexture3);
	backgroundSprite3.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture4;
	sf::Sprite backgroundSprite4;
	backgroundTexture4.loadFromFile("images/BackGrounds/w2_r.png");
	backgroundSprite4.setTexture(backgroundTexture4);
	backgroundSprite4.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture5;
	sf::Sprite backgroundSprite5;
	backgroundTexture5.loadFromFile("images/BackGrounds/w2_b.jpg");
	backgroundSprite5.setTexture(backgroundTexture5);
	backgroundSprite5.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture6;
	sf::Sprite backgroundSprite6;
	backgroundTexture6.loadFromFile("images/BackGrounds/w2_g.jpg");
	backgroundSprite6.setTexture(backgroundTexture6);
	backgroundSprite6.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture7;
	sf::Sprite backgroundSprite7;
	backgroundTexture7.loadFromFile("images/BackGrounds/w3_r.jpg");
	backgroundSprite7.setTexture(backgroundTexture7);
	backgroundSprite7.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture8;
	sf::Sprite backgroundSprite8;
	backgroundTexture8.loadFromFile("images/BackGrounds/w3_b.jpg");
	backgroundSprite8.setTexture(backgroundTexture8);
	backgroundSprite8.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

	sf::Texture backgroundTexture9;
	sf::Sprite backgroundSprite9;
	backgroundTexture9.loadFromFile("images/BackGrounds/w3_g.jpg");
	backgroundSprite9.setTexture(backgroundTexture9);
	backgroundSprite9.setColor(sf::Color(255, 255, 255, 255 *opacity)); 

    backgroundSprite = backgroundSprite1;

    Clock clock;                                //initiazing clock for managing snake movement Else it will move VERY FAST
    float delay=0.18 ,                           //Delay by which menu buttons will work
          speed=0.1;                            //Delay after which the snake will move

    Posfruit[0]=10;                 
    Posfruit[1]=10; 

    //For menu buttons present location
    int presentMenu=0 ,   /*For excape menu*/               presentBack=0 ,  //Background menu       
        presentMain=0 ,   /*For main menu */                presentMusic=0;  //Music menu

    int pos=350;            //Postions for menu buttons
    bool ShowMenu = 0 , playGame=0 ,        //Condtions of all the loops of game and menu
         ShowBackground=0 , mainMenu=1 ,
         gameOver=0 ,   overMenu=0,
         ShowMusic=0;


///////////////////////////////////////////////////////////////
//                  MAIN MENU INITIALIZING                   //
///////////////////////////////////////////////////////////////

    Text Heading;
    Heading.setFont(font);
	Heading.setCharacterSize(170);
	Heading.setFillColor(Color::White);
    Heading.setString( "SNAKE" );
    Heading.setPosition( 350 , 350 );

    Text Main[3];							

for( int i=0 ; i<3 ; i++ )
{   
    Main[i].setFont(font);
	Main[i].setCharacterSize(56);
	Main[i].setFillColor( i==0 ? Color::Red : Color::White );

    if( i==0 ){	      Main[i].setString( "Easy" );           Main[i].setPosition( 200 , 700 );}
    else if( i==1 ){  Main[i].setString( "Intermediate" );   Main[i].setPosition( 380 , 700 );}
    else if( i==2 ){  Main[i].setString( "Expert" );         Main[i].setPosition( 680 , 700 );}
}    

///////////////////////////////////////////////////////////////
//                 PAUSE MENU INITIALIZING                   //
///////////////////////////////////////////////////////////////
	
    Text Escape[5];						
 
 for( int i=0 ; i<5 ; i++ )
 {   
    Escape[i].setFont(font);
	Escape[i].setCharacterSize(70);
	Escape[i].setFillColor( i==0 ? Color::Red : Color::White );
	Escape[i].setPosition(400, 300 + (75*i));

    if( i==0 )	        Escape[i].setString( "Resume" );
    else if( i==1 )     Escape[i].setString( "Restart" );
    else if( i==2 )     Escape[i].setString( "Background" );
    else if( i==3 )     Escape[i].setString( "Music" );
    else if( i==4 )     Escape[i].setString( "Exit" );
}   

    Clock MenuClock , BackgroundClock;

///////////////////////////////////////////////////////////////
//                 MUSIC MENU INITIALIZING                   //
///////////////////////////////////////////////////////////////

   Text Music[5];							//Text for score
	
 
 for( int i=0 ; i<5 ; i++ )
 {   
    Music[i].setFont(font);
	Music[i].setCharacterSize(66);
	Music[i].setFillColor( i==0 ? Color::Red : Color::White );
	Music[i].setPosition(440, pos + (60*i));

    if( i==0 )	        Music[i].setString( "Music 1" );
    else if( i==1 )     Music[i].setString( "Music 2" );
    else if( i==2 )     Music[i].setString( "Music 3" );
    else if( i==3 )     Music[i].setString( "Music 4" );
    else if( i==4 )     Music[i].setString( "Music 5" );
}   



///////////////////////////////////////////////////////////////
//               BACKGROUND MENU INITIALIZING                //
///////////////////////////////////////////////////////////////

    Text BackSetting[12];							
	int bkPos = 69;

for( int i=0 ; i<12 ; i++ )
{   
    BackSetting[i].setFont(font);
	BackSetting[i].setCharacterSize( i==0 || i==4 ||  i==8 ? 70 : 56);
	BackSetting[i].setFillColor( i==0 ? Color::Red : Color::White );
	BackSetting[i].setPosition( i==0 || i==4 ||  i==8 ? 240 : 440 , bkPos + 69*i );

    if( i==0 )	         BackSetting[i].setString( "Back Ground 1" );
    else if( i==1 )      BackSetting[i].setString( "Red" );
    else if( i==2 )      BackSetting[i].setString( "Blue" );
    else if( i==3 )      BackSetting[i].setString( "Green" );
    else if( i==4 )      BackSetting[i].setString( "Back Ground 2" );
    else if( i==5 )      BackSetting[i].setString( "Red" );
    else if( i==6 )      BackSetting[i].setString( "Blue" );
    else if( i==7 )      BackSetting[i].setString( "Green" );
    else if( i==8 )      BackSetting[i].setString( "Back Ground 3" );
    else if( i==9 )      BackSetting[i].setString( "Red" );
    else if( i==10 )     BackSetting[i].setString( "Blue" );
    else if( i==11 )     BackSetting[i].setString( "Green" );

}   

///////////////////////////////////////////////////////////////
//                     MUSIC INITIALIZING                    //
///////////////////////////////////////////////////////////////


	sf::Music eat;
	eat.openFromFile("music/eat.wav");
	eat.setVolume(50);

	sf::Music menuMusic1;
	menuMusic1.openFromFile("music/menubutton.wav");
	menuMusic1.setVolume(50);

	sf::Music death;
	death.openFromFile("music/bonus.wav");
	death.setVolume(50);


    sf::Music bgMusic;
	// bgMusic.openFromFile("music/background/anime-ahh.wav");
	bgMusic.openFromFile("music/background/bg1.wav");
	bgMusic.setVolume(70);
    bgMusic.play();


while(window.isOpen()) {


///////////////////////////////////////////////////////////////
//                     Showing Main Menu                     //
///////////////////////////////////////////////////////////////

    while( mainMenu )
    {
        if( !(bgMusic.getStatus() == sf::Music::Playing) )     //Checking music status
        {
            bgMusic.stop();     bgMusic.play();
        }

		window.draw(backgroundSpriteMain);          //drawing background sprite

		sf::Event M;
		while (window.pollEvent(M)) {
			if (M.type == sf::Event::Closed)
        		return 0;		
            else if( Keyboard::isKeyPressed(Keyboard::Space) )
                return 0;
	    }		

        if ( MenuClock.getElapsedTime().asSeconds() > delay )       //If the time passed is greater than delay
        {
            MenuClock.restart();
            //This will change the color of the menu buttons i.e selected ones
            if( M.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left) ) )
            {
                if( presentMain == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 2;
                    Main[presentMain].setFillColor(FILL);
                }
                else if( presentMain == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 0;
                    Main[presentMain].setFillColor(FILL);
                }
                else if( presentMain == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 1;
                    Main[presentMain].setFillColor(FILL);
                }
            }
            else if( M.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right) ) )
            {
                if( presentMain == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 1;
                    Main[presentMain].setFillColor(FILL);
                }
                else if( presentMain == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 2;
                    Main[presentMain].setFillColor(FILL);
                }
                else if( presentMain == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Main[presentMain].setFillColor(Color::White);                    presentMain = 0;
                    Main[presentMain].setFillColor(FILL);
                }
            }
        }
        //Conditions when the certain button will be selected button 
        if (  M.key.code == sf::Keyboard::Enter && presentMain==0 )
        {   
            mainMenu=0;         gameOver=0; //Exit from menu
            speed = 0.2;        //speed setting
            playGame=1;         //Entering player area
        }
        else if (  M.key.code == sf::Keyboard::Enter && presentMain==1 )
        {   
            mainMenu=0;         gameOver=0;
            speed = 0.1;
            playGame=1;
        }
        else if (  M.key.code == sf::Keyboard::Enter && presentMain==2 )
        {   
            mainMenu=0;gameOver=0;
            speed = 0.05;
            playGame=1;
        }

        //Draw all options of easy , intermediate , and expert
        window.draw(Main[0]);
        window.draw(Main[1]);
        window.draw(Main[2]);
        window.draw( Heading ); //heading of SNAKE

        window.display();
        window.clear();
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
///////////////////////////////////////////////////////////////
//                     Music Menu                            //
///////////////////////////////////////////////////////////////
    

    while( ShowMusic )
    {
        if(  !(bgMusic.getStatus() == sf::Music::Playing)  )
        {
            bgMusic.stop();     bgMusic.play();
        }

		window.draw(backgroundSprite);          //drawing background sprite

		sf::Event Mu;
		while (window.pollEvent(Mu)) {
			if (Mu.type == sf::Event::Closed)
        		return 0;		
            else if( Keyboard::isKeyPressed(Keyboard::Escape) )
            {    ShowMusic=0;   ShowMenu=1;   }
	    }		

        if ( MenuClock.getElapsedTime().asSeconds() > delay )       //If the time passed is greater than delay
        {
            MenuClock.restart();
            if( Mu.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right) ) )
            {
                if( presentMusic == 0 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 4;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 1 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 0;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 2 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 1;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 3 )
                {
                    menuMusic1.stop();                 menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 2;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 4 )
                {
                    menuMusic1.stop();                 menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 3;
                    Music[presentMusic].setFillColor(FILL);
                }
            }
            else if( Mu.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left) ) )
            {
                if( presentMusic == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 1;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 2;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 3;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 3 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 4;
                    Music[presentMusic].setFillColor(FILL);
                }
                else if( presentMusic == 4 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Music[presentMusic].setFillColor(Color::White);                    presentMusic = 0;
                    Music[presentMusic].setFillColor(FILL);
                }
            }
        }

        if (  Mu.key.code == sf::Keyboard::Enter && presentMusic==0 )
        {   
            bgMusic.openFromFile("music/background/bg1.wav");
	        bgMusic.setVolume(70);
        }
        else if (  Mu.key.code == sf::Keyboard::Enter && presentMusic==1 )
        {   
      	    bgMusic.openFromFile("music/background/bg2.wav");
	        bgMusic.setVolume(70);
        }
        else if (  Mu.key.code == sf::Keyboard::Enter && presentMusic==2 )
        {   
     	    bgMusic.openFromFile("music/background/bg3.ogg");
	        bgMusic.setVolume(70);
        }
        else if (  Mu.key.code == sf::Keyboard::Enter && presentMusic==3 )
        {   
        	bgMusic.openFromFile("music/background/bg4.wav");
    	    bgMusic.setVolume(70);
        }
        else if (  Mu.key.code == sf::Keyboard::Enter && presentMusic==4 )
        {
  	        bgMusic.openFromFile("music/background/bg5.wav");
	        bgMusic.setVolume(70);
        }

        window.draw(Music[0]);
        window.draw(Music[1]);
        window.draw(Music[2]);
        window.draw(Music[3]);
        window.draw(Music[4]);

        window.display();
        window.clear();
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
///////////////////////////////////////////////////////////////
//                        Escape Menu                        //
///////////////////////////////////////////////////////////////
    

    while( ShowMenu )
    {
        if( !(bgMusic.getStatus() == sf::Music::Playing) )
        {
            bgMusic.stop();     bgMusic.play();
        }

		window.draw(backgroundSprite);          //drawing background sprite

		sf::Event m;
		while (window.pollEvent(m)) {
			if (m.type == sf::Event::Closed)
        		return 0;		
            else if( Keyboard::isKeyPressed(Keyboard::Space) )
                return 0;
	    }		

        if ( MenuClock.getElapsedTime().asSeconds() > delay )       //If the time passed is greater than delay
        {
            MenuClock.restart();
            if( m.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right) ) )
            {
                if( presentMenu == 0 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 4;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 1 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 0;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 2 )
                {
                    menuMusic1.stop();                 menuMusic1.play();
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 1;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 3 )
                {
                    menuMusic1.stop();                 menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 2;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 4 )
                {
                    menuMusic1.stop();                 menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 3;
                    Escape[presentMenu].setFillColor(FILL);
                }
            }
            else if( m.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left) ) )
            {
                if( presentMenu == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 1;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 2;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 3;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 3 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 4;
                    Escape[presentMenu].setFillColor(FILL);
                }
                else if( presentMenu == 4 )
                {
                    menuMusic1.stop();          menuMusic1.play();                    
                    Escape[presentMenu].setFillColor(Color::White);                    presentMenu = 0;
                    Escape[presentMenu].setFillColor(FILL);
                }
            }
        }

        if (  m.key.code == sf::Keyboard::Enter && presentMenu==0 )
        {   
            ShowMenu=0;               playGame=1;
            menuMusic1.stop();          menuMusic1.play();
        }
        else if (  m.key.code == sf::Keyboard::Enter && presentMenu==1 )
        {   
            ShowMenu=0;
            for( int i=0 ; i<size ; i++ )
            {   
                PosSnake[i][0]=0;                PosSnake[i][1]=0;
            }   
            menuMusic1.stop();          menuMusic1.play();
            size=4;     dir=0;          Head = DownHeadCent;
            playGame=1; overMenu=0;     score=0;
        }
        else if (  m.key.code == sf::Keyboard::Enter && presentMenu==2 )
        {   
            ShowMenu=0;                 ShowBackground=1;;
            menuMusic1.stop();          menuMusic1.play();        
        }
        else if (  m.key.code == sf::Keyboard::Enter && presentMenu==3 )
        {   
            ShowMenu=0;                 ShowMusic=1;;
            menuMusic1.stop();          menuMusic1.play();        
        }
        else if (  m.key.code == sf::Keyboard::Enter && presentMenu==4 )
            return 0;


        if( !overMenu ) window.draw(Escape[0]);
        window.draw(Escape[1]);
        window.draw(Escape[2]);
        window.draw(Escape[3]);
        window.draw(Escape[4]);

        window.display();
        window.clear();
    }

///////////////////////////////////////////////////////////////
//                     Back Ground Menu                      //
///////////////////////////////////////////////////////////////


while( ShowBackground )
{
        if(  !(bgMusic.getStatus() == sf::Music::Playing)  )
        {
            bgMusic.stop();     bgMusic.play();
        }

        window.draw(backgroundSprite);

		sf::Event b;
		while (window.pollEvent(b)) {
			if (b.type == sf::Event::Closed)
                return 0;        		
            else if( Keyboard::isKeyPressed(Keyboard::Escape) )
            {
                ShowBackground = 0;
                ShowMenu = 1;
            }
	    }		

       if ( BackgroundClock.getElapsedTime().asSeconds() > delay )       //If the time passed is greater than delay
        {
            BackgroundClock.restart();
            if( b.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right) ) )
            {
                if( presentBack == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 11;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 0;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 1;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                 else if( presentBack == 3 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 2;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 4 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 3;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 5 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 4;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 6 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 5;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 7 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 6;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 8 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 7;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 9 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 8;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 10 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 9;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 11 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 10;
                    BackSetting[presentBack].setFillColor(FILL);
                }
            }
            
            else if(b.type == sf::Event::KeyPressed && ( Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left) ) )
            {
                if( presentBack == 0 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 1;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 1 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 2;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 2 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 3;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 3 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 4;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 4 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 5;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 5 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 6;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 6 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 7;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 7 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 8;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 8 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 9;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 9 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 10;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 10 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 11;
                    BackSetting[presentBack].setFillColor(FILL);
                }
                else if( presentBack == 11 )
                {
                    menuMusic1.stop();          menuMusic1.play();                                        
                    BackSetting[presentBack].setFillColor(Color::White);                    presentBack = 0;
                    BackSetting[presentBack].setFillColor(FILL);
                }
            }
        }

        if (  b.key.code == sf::Keyboard::Enter && presentBack==1 )      {           backgroundSprite = backgroundSprite1; FILL = Color::Red;}
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==2 ) {           backgroundSprite = backgroundSprite2; FILL = Color::Blue; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==3 ) {           backgroundSprite = backgroundSprite3; FILL = Color::Green; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==5 ) {           backgroundSprite = backgroundSprite4; FILL = Color::Red; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==6 ) {           backgroundSprite = backgroundSprite5; FILL = Color::Blue; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==7 ) {           backgroundSprite = backgroundSprite6; FILL = Color::Green; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==9 ) {           backgroundSprite = backgroundSprite7; FILL = Color::Red; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==10 ){           backgroundSprite = backgroundSprite8; FILL = Color::Blue; }
        else if (  b.key.code == sf::Keyboard::Enter && presentBack==11 ){           backgroundSprite = backgroundSprite9; FILL = Color::Green; }

        window.draw(BackSetting[0]);
        window.draw(BackSetting[1]);
        window.draw(BackSetting[2]);
        window.draw(BackSetting[3]);
        window.draw(BackSetting[4]);
        window.draw(BackSetting[5]);
        window.draw(BackSetting[6]);
        window.draw(BackSetting[7]);
        window.draw(BackSetting[8]);
        window.draw(BackSetting[9]);
        window.draw(BackSetting[10]);
        window.draw(BackSetting[11]);
        
        window.display();
        window.clear();

    }

///////////////////////////////////////////////////////////////
//                      Play Game Loop                       //
///////////////////////////////////////////////////////////////

    while( playGame )
    {
        if(  !(bgMusic.getStatus() == sf::Music::Playing)  )
        {
            bgMusic.stop();     bgMusic.play();
        }

		window.draw(backgroundSprite);          //drawing background sprite

		sf::Event e1;                           //Initializing an event
		while (window.pollEvent(e1)) {
			if (e1.type == sf::Event::Closed)    //If event closes i.e we close the window it will terminate the program 
        		window.close();			
	        else if( Keyboard::isKeyPressed(Keyboard::Escape) ) 
		    {
                ShowMenu=1;
                playGame=0;
            }


        if (  e1.type == sf::Event::KeyPressed &&  Keyboard::isKeyPressed(Keyboard::Left)  && dir!=Right )     //If direction is not right and key pressed is left
        {
            Head = LHeadCent;               //Head sprite will be left head
            dir=Left;                       //Direction will change to left
        }
        else if ( e1.type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right) && dir!=Left )//If direction is not left and key pressed is right
        {   
            Head = RHeadCent;               //Head sprite will be right head
            dir=Right;                      //Direction will be changed to right
        }
        else if ( e1.type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up) && dir!=Down )//If direction is not down and key pressed is up
        {
            Head = UpHeadCent;              //Head sprite will by up side head
            dir=Up;                         //Direction will be changed to up
        }
        else if ( e1.type == sf::Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down)  && dir!=Up )//If direction is not up and key pressed is down
        {
            Head = DownHeadCent;            //Head sprite will down
            dir=Down;                       //Direction will be down    
        }
        }

        //Clock will check the time passed in sec
        if ( clock.getElapsedTime().asSeconds() > speed )       //If the time passed is greater than delay
        {
            clock.restart();                                    //Clock will restart again
            for (int i=size;i>0;--i)                            //This loop will iterate from size of snake to 0
            {
                PosSnake[i][0]=PosSnake[i-1][0];                //It will remove the first bead and step all left one's one step ahead
                PosSnake[i][1]=PosSnake[i-1][1];                //Both X and Y coordinates will be upadated
            }

            //Treating 1 as rows and 0 as column in (X) PosSnake[][X];  As the head is removed so we place the head according to the direction
            //Note: Both columns and rows are zero at top left; Rows are max at bottom i.e increasing when moving down and column are maximum at right most i.e are increasng when moving right

            if (dir==Down)          PosSnake[0][1] +=1;         //If Down: Row will be increased
            else if (dir==Up)       PosSnake[0][1] -=1;         //If Up: Row will decrease
            else if (dir==Left)     PosSnake[0][0] -=1;         //If Left: column will decrease
            else if (dir==Right)    PosSnake[0][0] +=1;         //If right: column will increase


            if ((PosSnake[0][0]==Posfruit[0]) && (PosSnake[0][1]==Posfruit[1])) 
            {
                size++;         score++;        
                eat.stop();     eat.play();
                Posfruit[0]=rand()%gameColumns;
                Posfruit[1]=rand()%gameColumns;
            }
        
            //Game over logic
            if ( PosSnake[0][1]>gameRows || PosSnake[0][1]<0 ||  PosSnake[0][0]>gameColumns || PosSnake[0][0]<0  ) 
            {    gameOver=1 ;      death.stop();     death.play();        overMenu=1;     }

            for (int i=1;i<size;i++)        //If snake collides with itself 
                if (PosSnake[0][0]==PosSnake[i][0] && PosSnake[0][1]==PosSnake[i][1])
                {    gameOver=1;        death.stop();     death.play();   overMenu=1;      }
        }


        for (int i=0;i<size;i++)            //It will iterate till the size of the snake
        {
            if( i==0 )                      //For first fragment 
            { 
                //It will multiply the locations with boxPixels for the specific location in the grid and set its position there
                Head.setPosition(PosSnake[i][0]*boxPixelsY, PosSnake[i][1]*boxPixelsX);
                window.draw(Head);          //THis will draw it there
            }
            else
            {
                //It will multiply the locations with boxPixels for the specific location in the grid and set its position there            
                verticalBodyCent.setPosition(PosSnake[i][0]*boxPixelsY, PosSnake[i][1]*boxPixelsX);
                window.draw(verticalBodyCent);            //For drawing
            }
        }

        Score.setString( "Score " + to_string(score) );
        fruit1.setPosition(Posfruit[0]*boxPixelsX, Posfruit[1]*boxPixelsX); //Setting position for fruit
        window.draw(fruit1);                                                //Drawing fruit
        window.draw(Score);

        //This will keep on showing the updated screem
        window.display();               //Displaiyng the window
        window.clear();                 //cLearing the window
    
    
///////////////////////////////////////////////////////////////
//                       Game Over Loop                      //
///////////////////////////////////////////////////////////////

        while( gameOver )
        {
            if(  !(bgMusic.getStatus() == sf::Music::Playing)  )
            {
                bgMusic.stop();     bgMusic.play();
            }

           window.draw(backgroundSprite);

      		sf::Event g;                           //Initializing an event
    		while (window.pollEvent(g)) {
    			if (g.type == sf::Event::Closed)    //If event closes i.e we close the window it will terminate the program 
           		    window.close();			
    	        else if( g.key.code == sf::Keyboard::Escape ) 
    		    {
                   mainMenu=1;     playGame=0;     gameOver=0;
                   dir=Down;       Head = DownHeadCent;       score=0;
                   
                   for( int i=0 ; i<size ; i++ )
                   {   PosSnake[i][0]=0;     PosSnake[i][1]=0;   }   
                   
                }
            }
            
            ScoreMain.setString( "Score is " + to_string(score) );

	        GameOver.setFillColor(FILL);
	        ScoreMain.setFillColor(FILL);
            
            window.draw(ScoreMain);
            window.draw(GameOver);
            
            window.display();               //Displaiyng the window
            window.clear();                 //cLearing the window
        }        
    }
}

    
    
    return 0;
}


