> 其实这题是我从另外一个比赛上面扒过来的，源码里面的变量名都是反编译器反编译出来的变量名，我没有修改过...

* 关键就在于Check函数：

  ```java
  public static boolean CHECK(int input)
    {
      if ((input > 10000000) && (input < 99999999))
      {
        int v7 = 1;
        int v8 = 10000000;
        int v3 = 1;
        if ((Math.abs(input / 1000 % 100 - 80) == 3) && (input % 1000 % 927 == 0))
        {
          int v5 = 0;
          while (v5 < 4)
          {
            if (input / v7 % 10 != input / v8 % 10)
            {
              v3 = 0;
              break;
            }
            v7 *= 10;
            v8 /= 10;
            v5++;
          }
          if (v3 != 1) {
            return false;
          }
          if (v3 == 1) {
            return true;
          }
        }
      }
      return false;
    }
  ```

* 大概逻辑就是一个回文数的判断，然后通过数学运算限定了后面几位，获得前面几位后输入就可以得到flag