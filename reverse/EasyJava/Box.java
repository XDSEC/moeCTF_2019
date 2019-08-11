package qqq;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Box
  implements ActionListener
{
  int size = 9;
  JButton[] jbs = new JButton[this.size];
  JPanel jp;
  JPanel jp1;
  JFrame jf;
  JLabel la;
  JTextField txt;
  JTextField tx;
  JLabel jt;
  JButton bt;
  JButton bt1;
  String a = "";
  
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
  
  public Box()
  {
    this.jp = new JPanel();
    this.jp1 = new JPanel();
    this.jf = new JFrame();
    this.jf.setDefaultCloseOperation(3);
    this.tx = new JTextField(16);
    this.jt = new JLabel("Input passwd to change your flag!!!!!!!!!");
    this.bt = new JButton("check");
    this.bt1 = new JButton("clear");
    this.bt1.addActionListener(this);
    this.bt.addActionListener(this);
    this.la = new JLabel("Passwd:");
    
    this.txt = new JTextField(16);
    this.txt.setEnabled(false);
    this.jp1.add(this.la);
    this.jp1.add(this.txt);
    this.jp1.add(this.bt);
    this.jp1.add(this.bt1);
    this.jp1.add(this.jt);
    this.jp1.add(this.tx);
    this.jp.setLayout(new GridLayout(3, 3));
    for (int i = 0; i < this.size; i++)
    {
      this.jbs[i] = new JButton(String.valueOf(i + 1));
      this.jbs[i].addActionListener(this);
    }
    this.jf.setLayout(new GridLayout(2, 1));
    this.jf.add(this.jp1);
    this.jf.add(this.jp);
    for (int i = 0; i < this.size; i++) {
      this.jp.add(this.jbs[i]);
    }
    this.jf.setTitle("Box");
    this.jf.setSize(300, 400);
    this.jf.setDefaultCloseOperation(3);
    this.jf.setLocation(200, 200);
    
    this.jf.setVisible(true);
  }
  
  public static void main(String[] args)
  {
    new Box();
  }
  
  
  public void actionPerformed(ActionEvent e)
  {
    if (e.getSource() == this.jbs[0])
    {
      this.a += '1';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[1])
    {
      this.a += '2';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[2])
    {
      this.a += '3';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[3])
    {
      this.a += '4';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[4])
    {
      this.a += '5';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[5])
    {
      this.a += '6';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[6])
    {
      this.a += '7';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[7])
    {
      this.a += '8';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.jbs[8])
    {
      this.a += '9';
      this.txt.setText(this.a);
    }
    if (e.getSource() == this.bt) {
      if (CHECK(Integer.parseInt(this.a))) {
        this.tx.setText("moectf{" + (char)(Integer.parseInt(this.a) / 1000000) + (char)(Integer.parseInt(this.a) / 10000 % 100) + (char)(Integer.parseInt(this.a) / 100 % 100) + "_he}");
      } else {
        this.tx.setText("clear and try again!");
      }
    }
    if (e.getSource() == this.bt1)
    {
      this.txt.setText("");
      this.tx.setText("");
      this.a = "";
    }
  }
}