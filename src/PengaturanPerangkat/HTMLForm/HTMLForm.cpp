#include "HTMLForm.h"
#include <Arduino.h>

//Public
String HTMLForm::login(String target, String message){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membuat kode HTML halaman login.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  String html = "";
  html += "<html>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Login</title>";
  html += "<style>a{   color: #0000FF;   text-decoration: underline;}a:visited{   color: #800080;}a:active{   color: #FF0000;}a:hover{   color: #0000FF;   text-decoration: underline;}input:focus, textarea:focus, select:focus{   outline: none;}.visibility-hidden{   visibility: hidden;}h1, .h1{   font-family: Arial;   font-weight: bold;   font-size: 32px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h2, .h2{   font-family: Arial;   font-weight: bold;   font-size: 27px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h3, .h3{   font-family: Arial;   font-weight: bold;   font-size: 24px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h4, .h4{   font-family: Arial;   font-weight: bold;   font-size: 21px;   font-style: italic;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h5, .h5{   font-family: Arial;   font-weight: bold;   font-size: 19px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h6, .h6{   font-family: Arial;   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}.CustomStyle{   font-family: \"Courier New\";   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #2E74B5;   background-color: transparent;}div#container{   width: 363px;   position: relative;   margin: 0 auto 0 auto;   text-align: left;}body{   background-color: #FFFFFF;   color: #000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 1.1875;   margin: 0;   text-align: center;}#wb_Form1{   background-color: #FBFBFB;   background-image: none;   border: 0px solid #CCCCCC;}#Label1{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox1{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox1:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label2{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox2{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox2:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Button1{   border: 1px solid #2E6DA4;   border-radius: 4px;   background-color: #3370B7;   background-image: none;   color: #FFFFFF;   font-family: Arial;   font-weight: normal;   font-size: 13px;   -webkit-appearance: none;   margin: 0;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<div id=\"container\">";
  html += "<div style=\"position:absolute;left:30px;top:0px;width:302px;height:122px;z-index:5;\">";
  html += "<form method=\"post\" action=\"";
  html += target;
  html += "\">";
  html += "<label for=\"Editbox1\" id=\"Label1\" style=\"position:absolute;left:10px;top:15px;width:70px;height:26px;line-height:26px;z-index:0;\">Username :</label>";
  html += "<input type=\"text\" id=\"Editbox1\" style=\"position:absolute;left:88px;top:14px;width:190px;height:26px;z-index:1;\" name=\"username\" value=\"\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Editbox2\" id=\"Label2\" style=\"position:absolute;left:10px;top:46px;width:70px;height:26px;line-height:26px;z-index:2;\">Password :</label>";
  html += "<input type=\"password\" id=\"Editbox2\" style=\"position:absolute;left:88px;top:45px;width:190px;height:26px;z-index:3;\" name=\"password\" value=\"\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<input type=\"submit\" id=\"Button1\" name=\"\" value=\"Login\" style=\"position:absolute;left:103px;top:82px;width:96px;height:25px;z-index:4;\">";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  if(message != ""){
    html += "<script type=\"text/javascript\">alert(\"";
    html += message;
    html += "\");</script>";
  }
  html += "</body>";
  html += "</html>";
  return html;
}

String HTMLForm::pengaturanKoneksi(String target, String message, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout, String wifi_ssid, String wifi_password, String mqtt_broker, String mqtt_username, String mqtt_password){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membuat kode HTML halaman pengaturan koneksi.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  String html = "";
  html += "<html>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Home Automation</title>";
  html += "<style>a{   color: #0000FF;   text-decoration: underline;}a:visited{   color: #800080;}a:active{   color: #FF0000;}a:hover{   color: #0000FF;   text-decoration: underline;}input:focus, textarea:focus, select:focus{   outline: none;}.visibility-hidden{   visibility: hidden;}h1, .h1{   font-family: Arial;   font-weight: bold;   font-size: 32px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h2, .h2{   font-family: Arial;   font-weight: bold;   font-size: 27px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h3, .h3{   font-family: Arial;   font-weight: bold;   font-size: 24px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h4, .h4{   font-family: Arial;   font-weight: bold;   font-size: 21px;   font-style: italic;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h5, .h5{   font-family: Arial;   font-weight: bold;   font-size: 19px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h6, .h6{   font-family: Arial;   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}.CustomStyle{   font-family: \"Courier New\";   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #2E74B5;   background-color: transparent;}div#container{   width: 560px;   position: relative;   margin: 0 auto 0 auto;   text-align: left;}body{   background-color: #FFFFFF;   color: #000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 1.1875;   margin: 0;   text-align: center;}#menu{   text-align: left;   float: left;   margin: 0;   width: 100%;   font-family: Arial;   font-weight: normal;   font-size: 13px;   list-style-type: none;   padding: 15px 0px 4px 10px;   overflow: hidden;}#menu li{   float: left;}#menu li a.active, #menu li a:hover.active{   position: relative;   font-weight: normal;   text-decoration: none;   z-index: 2;}#menu li a{   padding: 5px 14px 8px 14px;   margin-right: 3px;   text-decoration: none;   border-bottom: none;   position: relative;   top: 0;   -webkit-transition: 200ms all linear;   -moz-transition: 200ms all linear;   transition: 200ms all linear;}#menu li a:hover{   font-weight: normal;   text-decoration: none;   top: -4px;}#menu{   border-bottom: 1px solid #C0C0C0;}#menu li a.active, #menu li a:hover.active{   background-color: #FFFFFF;   color: #666666;}#menu li a{   border: 1px solid #C0C0C0;   border-top-left-radius: 5px;   border-top-right-radius: 5px;   background-color: #EEEEEE;   color: #666666;}#menu li a:hover{   background: #C0C0C0;   color: #666666;}#wb_Form1{   background-color: #FBFBFB;   background-image: none;   border: 0px solid #CCCCCC;}#Label1{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox1{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox1:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label2{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox2{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox2:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Button1{   border: 1px solid #2E6DA4;   border-radius: 4px;   background-color: #3370B7;   background-image: none;   color: #FFFFFF;   font-family: Arial;   font-weight: normal;   font-size: 13px;   -webkit-appearance: none;   margin: 0;}#Editbox3{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox3:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label3{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Label4{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox4{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox4:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label5{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox5{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox5:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<div id=\"container\">";
  html += "<div id=\"wb_menu\" style=\"position:absolute;left:8px;top:0px;width:540px;height:34px;z-index:11;overflow:hidden;\">";
  html += "<ul id=\"menu\">";
  html += "<li><a href=\"";
  html += link_pengaturan_koneksi;
  html += "\" title=\"Home Automation\" class=\"active\">Pengaturan Koneksi</a></li>";
  html += "<li><a href=\"";
  html += link_pengaturan_pengguna;
  html += "\" title=\"Home Automation\">Pengaturan Pengguna</a></li>";
  html += "<li><a href=\"";
  html += link_informasi_firmware;
  html += "\" title=\"Home Automation\">Informasi Firmware</a></li>";
  html += "<li><a href=\"";
  html += link_logout;
  html += "\">Logout</a></li>";
  html += "</ul>";
  html += "</div>";
  html += "<div id=\"wb_Form1\" style=\"position:absolute;left:8px;top:36px;width:540px;height:215px;z-index:12;\">";
  html += "<form method=\"post\" action=\"";
  html += target;
  html += "\" id=\"Form1\">";
  html += "<label for=\"Label1\" id=\"Label1\" style=\"position:absolute;left:10px;top:15px;width:102px;height:26px;line-height:26px;z-index:0;\">Wi-Fi SSID</label>";
  html += "<input type=\"text\" id=\"Editbox1\" style=\"position:absolute;left:130px;top:14px;width:400px;height:26px;z-index:4;\" name=\"wifi_ssid\" value=\"";
  html += wifi_ssid;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label2\" id=\"Label2\" style=\"position:absolute;left:10px;top:46px;width:112px;height:26px;line-height:26px;z-index:1;\">Wi-Fi Password</label>";
  html += "<input type=\"password\" id=\"Editbox2\" style=\"position:absolute;left:130px;top:45px;width:400px;height:26px;z-index:2;\" name=\"wifi_password\" value=\"";
  html += wifi_password;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label3\" id=\"Label3\" style=\"position:absolute;left:10px;top:77px;width:112px;height:26px;line-height:26px;z-index:5;\">MQTT Broker</label>";
  html += "<input type=\"text\" id=\"Editbox3\" style=\"position:absolute;left:130px;top:76px;width:400px;height:26px;z-index:6;\" name=\"mqtt_broker\" value=\"";
  html+= mqtt_broker;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label4\" id=\"Label4\" style=\"position:absolute;left:10px;top:108px;width:112px;height:26px;line-height:26px;z-index:7;\">MQTT Username</label>";
  html += "<input type=\"text\" id=\"Editbox4\" style=\"position:absolute;left:130px;top:107px;width:400px;height:26px;z-index:8;\" name=\"mqtt_username\" value=\"";
  html += mqtt_username;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label5\" id=\"Label5\" style=\"position:absolute;left:10px;top:139px;width:112px;height:26px;line-height:26px;z-index:9;\">MQTT Password</label>";
  html += "<input type=\"password\" id=\"Editbox5\" style=\"position:absolute;left:130px;top:138px;width:400px;height:26px;z-index:10;\" name=\"mqtt_password\" value=\"";
  html += mqtt_password;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<input type=\"submit\" id=\"Button1\" name=\"\" value=\"Simpan\" style=\"position:absolute;left:142px;top:175px;width:96px;height:25px;z-index:3;\">";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  if(message != ""){
    html += "<script type=\"text/javascript\">alert(\"";
    html += message;
    html += "\");</script>";
  }
  html += "</body>";
  html += "</html>";
  return html;
}

String HTMLForm::pengaturanPengguna(String target, String message, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout, String username, String password, String konfirmasi_password){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membuat kode HTML halaman pengaturan pengguna.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  String html = "";
  html += "<html>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Home Automation</title>";
  html += "<style>a{   color: #0000FF;   text-decoration: underline;}a:visited{   color: #800080;}a:active{   color: #FF0000;}a:hover{   color: #0000FF;   text-decoration: underline;}input:focus, textarea:focus, select:focus{   outline: none;}.visibility-hidden{   visibility: hidden;}h1, .h1{   font-family: Arial;   font-weight: bold;   font-size: 32px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h2, .h2{   font-family: Arial;   font-weight: bold;   font-size: 27px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h3, .h3{   font-family: Arial;   font-weight: bold;   font-size: 24px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h4, .h4{   font-family: Arial;   font-weight: bold;   font-size: 21px;   font-style: italic;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h5, .h5{   font-family: Arial;   font-weight: bold;   font-size: 19px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h6, .h6{   font-family: Arial;   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}.CustomStyle{   font-family: \"Courier New\";   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #2E74B5;   background-color: transparent;}div#container{   width: 560px;   position: relative;   margin: 0 auto 0 auto;   text-align: left;}body{   background-color: #FFFFFF;   color: #000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 1.1875;   margin: 0;   text-align: center;}#menu{   text-align: left;   float: left;   margin: 0;   width: 100%;   font-family: Arial;   font-weight: normal;   font-size: 13px;   list-style-type: none;   padding: 15px 0px 4px 10px;   overflow: hidden;}#menu li{   float: left;}#menu li a.active, #menu li a:hover.active{   position: relative;   font-weight: normal;   text-decoration: none;   z-index: 2;}#menu li a{   padding: 5px 14px 8px 14px;   margin-right: 3px;   text-decoration: none;   border-bottom: none;   position: relative;   top: 0;   -webkit-transition: 200ms all linear;   -moz-transition: 200ms all linear;   transition: 200ms all linear;}#menu li a:hover{   font-weight: normal;   text-decoration: none;   top: -4px;}#menu{   border-bottom: 1px solid #C0C0C0;}#menu li a.active, #menu li a:hover.active{   background-color: #FFFFFF;   color: #666666;}#menu li a{   border: 1px solid #C0C0C0;   border-top-left-radius: 5px;   border-top-right-radius: 5px;   background-color: #EEEEEE;   color: #666666;}#menu li a:hover{   background: #C0C0C0;   color: #666666;}#wb_Form1{   background-color: #FBFBFB;   background-image: none;   border: 0px solid #CCCCCC;}#Label1{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox1{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox1:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label2{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox2{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox2:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Button1{   border: 1px solid #2E6DA4;   border-radius: 4px;   background-color: #3370B7;   background-image: none;   color: #FFFFFF;   font-family: Arial;   font-weight: normal;   font-size: 13px;   -webkit-appearance: none;   margin: 0;}#Editbox3{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox3:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label3{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<div id=\"container\">";
  html += "<div id=\"wb_menu\" style=\"position:absolute;left:8px;top:0px;width:540px;height:34px;z-index:7;overflow:hidden;\">";
  html += "<ul id=\"menu\">";
  html += "<li><a href=\"";
  html += link_pengaturan_koneksi;
  html += "\" title=\"Home Automation\">Pengaturan Koneksi</a></li>";
  html += "<li><a href=\"";
  html += link_pengaturan_pengguna;
  html += "\" title=\"Home Automation\" class=\"active\">Pengaturan Pengguna</a></li>";
  html += "<li><a href=\"";
  html += link_informasi_firmware;
  html += "\" title=\"Home Automation\">Informasi Firmware</a></li>";
  html += "<li><a href=\"";
  html += link_logout;
  html += "\">Logout</a></li>";
  html += "</ul>";
  html += "</div>";
  html += "<div id=\"wb_Form1\" style=\"position:absolute;left:8px;top:36px;width:540px;height:154px;z-index:8;\">";
  html += "<form method=\"post\" action=\"";
  html += target;
  html += "\" id=\"Form1\">";
  html += "<label for=\"Label1\" id=\"Label1\" style=\"position:absolute;left:10px;top:15px;width:102px;height:26px;line-height:26px;z-index:0;\">Username</label>";
  html += "<input type=\"text\" id=\"Editbox1\" style=\"position:absolute;left:150px;top:14px;width:380px;height:26px;z-index:4;\" name=\"username\" value=\"";
  html += username;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label2\" id=\"Label2\" style=\"position:absolute;left:10px;top:46px;width:112px;height:26px;line-height:26px;z-index:1;\">Password</label>";
  html += "<input type=\"password\" id=\"Editbox2\" style=\"position:absolute;left:150px;top:45px;width:380px;height:26px;z-index:2;\" name=\"password\" value=\"";
  html += password;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<label for=\"Label3\" id=\"Label3\" style=\"position:absolute;left:10px;top:77px;width:124px;height:26px;line-height:26px;z-index:5;\">Konfirmasi Password</label>";
  html += "<input type=\"password\" id=\"Editbox3\" style=\"position:absolute;left:150px;top:76px;width:380px;height:26px;z-index:6;\" name=\"konfirmasi_password\" value=\"";
  html += konfirmasi_password;
  html += "\" maxlength=\"32\" spellcheck=\"false\">";
  html += "<input type=\"submit\" id=\"Button1\" name=\"\" value=\"Simpan\" style=\"position:absolute;left:150px;top:117px;width:96px;height:25px;z-index:3;\">";
  html += "</form>";
  html += "</div>";
  html += "</div>";
  if(message != ""){
    html += "<script type=\"text/javascript\">alert(\"";
    html += message;
    html += "\");</script>";
  }
  html += "</body>";
  html += "</html>";
  return html;
}

String HTMLForm::informasiFirmware(FIRMWARE_IN informasi_firmware, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membuat kode HTML halaman informasi firmware.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  String html = "";
  html += "<html>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<title>Home Automation</title>";
  html += "<style>a{   color: #0000FF;   text-decoration: underline;}a:visited{   color: #800080;}a:active{   color: #FF0000;}a:hover{   color: #0000FF;   text-decoration: underline;}input:focus, textarea:focus, select:focus{   outline: none;}.visibility-hidden{   visibility: hidden;}h1, .h1{   font-family: Arial;   font-weight: bold;   font-size: 32px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h2, .h2{   font-family: Arial;   font-weight: bold;   font-size: 27px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h3, .h3{   font-family: Arial;   font-weight: bold;   font-size: 24px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h4, .h4{   font-family: Arial;   font-weight: bold;   font-size: 21px;   font-style: italic;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h5, .h5{   font-family: Arial;   font-weight: bold;   font-size: 19px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}h6, .h6{   font-family: Arial;   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #000000;   background-color: transparent;   margin: 0px 0px 0px 0px;   padding: 0px 0px 0px 0px;   display: inline;}.CustomStyle{   font-family: \"Courier New\";   font-weight: bold;   font-size: 16px;   text-decoration: none;   color: #2E74B5;   background-color: transparent;}div#container{   width: 560px;   position: relative;   margin: 0 auto 0 auto;   text-align: left;}body{   background-color: #FFFFFF;   color: #000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 1.1875;   margin: 0;   text-align: center;}#menu{   text-align: left;   float: left;   margin: 0;   width: 100%;   font-family: Arial;   font-weight: normal;   font-size: 13px;   list-style-type: none;   padding: 15px 0px 4px 10px;   overflow: hidden;}#menu li{   float: left;}#menu li a.active, #menu li a:hover.active{   position: relative;   font-weight: normal;   text-decoration: none;   z-index: 2;}#menu li a{   padding: 5px 14px 8px 14px;   margin-right: 3px;   text-decoration: none;   border-bottom: none;   position: relative;   top: 0;   -webkit-transition: 200ms all linear;   -moz-transition: 200ms all linear;   transition: 200ms all linear;}#menu li a:hover{   font-weight: normal;   text-decoration: none;   top: -4px;}#menu{   border-bottom: 1px solid #C0C0C0;}#menu li a.active, #menu li a:hover.active{   background-color: #FFFFFF;   color: #666666;}#menu li a{   border: 1px solid #C0C0C0;   border-top-left-radius: 5px;   border-top-right-radius: 5px;   background-color: #EEEEEE;   color: #666666;}#menu li a:hover{   background: #C0C0C0;   color: #666666;}#wb_Form1{   background-color: #FBFBFB;   background-image: none;   border: 0px solid #CCCCCC;}#Label1{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox1{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox1:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label2{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Editbox2{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox2:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Button1{   border: 1px solid #2E6DA4;   border-radius: 4px;   background-color: #3370B7;   background-image: none;   color: #FFFFFF;   font-family: Arial;   font-weight: normal;   font-size: 13px;   -webkit-appearance: none;   margin: 0;}#Editbox3{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox3:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Editbox4{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox4:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Editbox5{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox5:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Editbox6{   border: 1px solid #CCCCCC;   border-radius: 4px;   background-color: #FFFFFF;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   line-height: 16px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;}#Editbox6:focus{   border-color: #66AFE9;   box-shadow: inset 0px 1px 1px rgba(0,0,0,0.075), 0px 0px 8px rgba(102,175,233,0.60);   outline: 0;}#Label3{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Label4{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Label5{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}#Label6{   border: 0px solid #CCCCCC;   border-radius: 4px;   background-color: transparent;   background-image: none;   color :#000000;   font-family: Arial;   font-weight: normal;   font-size: 13px;   padding: 4px 4px 4px 4px;   margin: 0;   text-align: left;   vertical-align: top;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<div id=\"container\">";
  html += "<div id=\"wb_menu\" style=\"position:absolute;left:8px;top:0px;width:540px;height:34px;z-index:7;overflow:hidden;\">";
  html += "<ul id=\"menu\">";
  html += "<li><a href=\"";
  html += link_pengaturan_koneksi;
  html += "\" title=\"Home Automation\">Pengaturan Koneksi</a></li>";
  html += "<li><a href=\"";
  html += link_pengaturan_pengguna;
  html += "\" title=\"Home Automation\">Pengaturan Pengguna</a></li>";
  html += "<li><a href=\"";
  html += link_informasi_firmware;
  html += "\" title=\"Home Automation\" class=\"active\">Informasi Firmware</a></li>";
  html += "<li><a href=\"";
  html += link_logout;
  html += "\">Logout</a></li>";
  html += "</ul>";
  html += "</div>";
  html += "<div id=\"wb_Form1\" style=\"position:absolute;left:8px;top:36px;width:540px;height:210px;z-index:8;\">";
  html += "<label for=\"Label1\" id=\"Label1\" style=\"position:absolute;left:10px;top:15px;width:124px;height:26px;line-height:26px;z-index:0;\">Firmware Name</label>";
  html += "<input type=\"text\" id=\"Editbox1\" style=\"position:absolute;left:150px;top:14px;width:380px;height:26px;z-index:4;\" value=\"";
  html += informasi_firmware.firmwareName;
  html += "\" spellcheck=\"false\" readonly>";
  html += "<label for=\"Label2\" id=\"Label2\" style=\"position:absolute;left:10px;top:46px;width:124px;height:26px;line-height:26px;z-index:1;\">Firmware Description</label>";
  html += "<input type=\"text\" id=\"Editbox2\" style=\"position:absolute;left:150px;top:45px;width:380px;height:26px;z-index:2;\" value=\"";
  html += informasi_firmware.firmwareDescription;
  html += "\" spellcheck=\"false\" readonly>";
  html += "<label for=\"Label3\" id=\"Label3\" style=\"position:absolute;left:10px;top:77px;width:124px;height:26px;line-height:26px;z-index:5;\">Firmware Version</label>";
  html += "<input type=\"text\" id=\"Editbox3\" style=\"position:absolute;left:150px;top:76px;width:380px;height:26px;z-index:6;\" value=\"";
  html += informasi_firmware.firmwareVersion;
  html += "\" spellcheck=\"false\" readonly>";
  html += "<label for=\"Label4\" id=\"Label4\" style=\"position:absolute;left:10px;top:108px;width:124px;height:26px;line-height:26px;z-index:5;\">Legal Copyright</label>";
  html += "<input type=\"text\" id=\"Editbox4\" style=\"position:absolute;left:150px;top:107px;width:380px;height:26px;z-index:6;\" value=\"";
  html += informasi_firmware.legalCopyright;
  html += "\" spellcheck=\"false\" readonly>";
  html += "<label for=\"Label5\" id=\"Label5\" style=\"position:absolute;left:10px;top:139px;width:124px;height:26px;line-height:26px;z-index:5;\">Company Name</label>";
  html += "<input type=\"text\" id=\"Editbox5\" style=\"position:absolute;left:150px;top:138px;width:380px;height:26px;z-index:6;\" value=\"";
  html += informasi_firmware.companyName;
  html += "\" spellcheck=\"false\" readonly>";
  html += "<label for=\"Label6\" id=\"Label6\" style=\"position:absolute;left:10px;top:170px;width:124px;height:26px;line-height:26px;z-index:5;\">Firmware Type</label>";
  html += "<input type=\"text\" id=\"Editbox6\" style=\"position:absolute;left:150px;top:169px;width:380px;height:26px;z-index:6;\" value=\"";
  html += informasi_firmware.firmwareType;
  html += "\" spellcheck=\"false\" readonly>";
  html += "</div>";
  html += "</div>";
  html += "</body>";
  html += "</html>";
  return html; 
}

String HTMLForm::getArg(HTML_FORM_ARG arg){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk mendapatkan arg pada Form HTML.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return htmlFormArg[arg];
}
//------------------------------------------------------------------------------
