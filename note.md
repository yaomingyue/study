#c语言技巧
##c语言的输入函数解决输入回车问题

scanf("%c%*c",&a);* 

##C/C++ linux下光标定位和清屏函数  设置背景色

http://www.cnblogs.com/yangyangye/articles/1771821.html

printf("\033[31m####---->>\033[32m""hello\n\033[m");//后跟\033[m
是将颜色置none,防止后边打印的也是这个颜色

  printf("\033[43;31m");   // 设置背景颜色 

  printf("\33[2J");   //清屏 

  printf("\33[9;8H");   //设置光标位置 

  //printf("\33[4m");//下划线
                
  printf("\033[?25h");   //显示光标 
                 
   //printf("\033[8A");   //将光标上移8行 

   printf("\33[%d;8H",j);   //设置光标位置 
