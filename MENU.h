#ifndef MENU_H
#define MENU_H
#include "Arduino.h"
#include "U8g2lib.h"
class MENU
{
  private:
  
      U8G2 _u8g2;
      int strwidth;
    String menu_item[50];
    String id_item[50];
    String _title;
    int state;
    int _diastate;
    int last_item;
    String _diatitle[2];
    int _diares;
   // char *token;
  public:
    

    void up();
    void dwn();
    String getSelect();
    MENU(String,char*,U8G2 u8);
    MENU(U8G2 u8);
    MENU();
    ~MENU();
    String getDia();
    void _diaup();
    void _diadwn();
    void display_menu();
    void dialog_box(char*,int,int);

};



#endif
