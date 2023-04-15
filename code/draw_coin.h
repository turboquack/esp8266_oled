#pragma once

int screen_x=128;
int screen_y=64;
//TXT POS
int line_1_y = screen_y*0;
int line_2_y = screen_y*0.25;
int line_3_y = screen_y*0.50;
int line_4_y = screen_y*0.75;
int out_of_screen_pos_x = (screen_x*1.2)*-1;
//TXT POS

void u8g2_prepare(void) 
{
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void show_coin(String coin_name, double price,String change1_desc, double change1,String change2_desc, double change2)
{
  
  String change24h_s=String(change2).c_str();
  String change1h_s=String(change1).c_str();
  String price_s=String(price).c_str();
  price_s=price_s+" $";

  int pos_text_x = 120;

  change1_desc=change1_desc+String(change1).c_str();
  change2_desc=change2_desc+String(change2).c_str();
    
  if (change1<=0)
  {
    change1_desc=change1_desc+"⬇% ↓";
  }
  else
  {
    change1_desc=change1_desc+"⬇%  ↑";
  }
    
  if (change2<=0)
  {
    change2_desc=change2_desc+"⬇% ↓";
  }
  else
  {
    change2_desc=change2_desc+"⬇% ↑";
  }
    
  bool draw_flag=true;

  while(draw_flag==true)
  { 
    u8g2.clearBuffer();

    //COIN NAME
    u8g2.drawStr( pos_text_x, line_1_y, coin_name.c_str());
    //COIN NAME

    //COIN PRICE
    u8g2.drawStr( pos_text_x, line_2_y, String(price_s).c_str());
    //COIN PRICE

    //COIN CHANGE 1H
    u8g2.drawUTF8( pos_text_x, line_3_y, change1_desc.c_str());
    //COIN CHANGE 1H

    //COIN CHANGE 24H
    u8g2.drawUTF8( pos_text_x, line_4_y, change2_desc.c_str());
    //COIN CHANGE 24H

    u8g2.sendBuffer();
      
    pos_text_x=pos_text_x-1;

    yield();
    if (pos_text_x<out_of_screen_pos_x)
    {
      draw_flag=false;
    }
  }      
}
