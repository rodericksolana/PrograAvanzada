/*Rodrigo Solana Chao
  A01129839 Proyecto 2do Parcial
  Álgebra Lineal
  sitio base de apoyo:
  https://processing.org/tutorials/transform2d/ 
*/
/*Declaración variables globales*/
int armAngle = 0;
int armAngle2=0;
int angleChange = 2;
int x=280; int y=60; float t=.5;
final int ANGLE_LIMIT = 90;
int op=0;
int sNum2=0;
int aux=0;
void setup ()
{
  size (400,400,P3D);
  smooth();
  //frameRate(70);
  frameRate(20);
}//Cierre de setup


void draw ()
{
  background(255);//Color del fondo
  lights();
  pushMatrix();
  fill (255,0,0);
  text ("1) Golpe\n2) Patada \n3) Poder \n4) Cerrar Aplicación",10,20);
  text ("Selección:  " + op,200,30);
    if(op==0)
    {
      text ("Selecciona una opción ",200,60);
    }
      else if(op==1)
      {
        text ("Seleccionaste Golpe ",200,60);
        drawRobot();
        armAngle += angleChange;
      // if the arm has moved past its limit,
      // reverse direction and set within limits.
        if (armAngle > ANGLE_LIMIT || armAngle < 0)
        {
          angleChange = -angleChange;
          armAngle += angleChange;
        }
        x=280; y=60;
    }//Cierre de if op1
    
    else if (op==2)
      {
      text ("Seleccionaste Patada ",200,60);
       drawRobot();
       armAngle += angleChange;
        if (armAngle > ANGLE_LIMIT || armAngle < 0)
        {
          angleChange = -angleChange;
          armAngle += angleChange;
        }//Cierre de if interno
        x=280; y=60;
      }//Cierre de else op2
     else if (op==3)
      {
 
        text ("Seleccionaste Poder ",200,60);
        drawRobot();
        armAngle2 += angleChange;
          if (armAngle2 > 38 || armAngle2 < 0)
          {
            angleChange = -angleChange;
            armAngle2 += angleChange;
          }//Cierre de if interno
         if(armAngle2<=0)
         {
          x=280; y=60;
         }
      }//Cierre de else op3
     else if (op==4)
      {
       System.exit(0); 
      }//Cierre de op4
    else
    {
      text ("Esa opción no es válida ",200,60);
      x=280; y=60;
    }//Cierre de else
      popMatrix();
}//Cierre de función draw


void keyPressed ()
{
  if (key=='\n')  
  {
    sNum2=op;
    op=0;
  }else
    op=Character.getNumericValue(key);
}//Cierre para leer de teclado

void drawRobot()
{
  noStroke();
  fill(38, 38, 200);
  rect(120, 150, 38, 30); // cabeza 
  rect(114, 182, 50, 50); // cuerpo
  drawLeftArm();
  drawRightArm();
  rect(122, 234, 16, 50); // se dibuja la pierna izquierda
  drawPierna();
  //rect(140, 234, 16, 50); // se dibuja la pierna derecha
  
  fill(222, 222, 249);
  ellipse(130, 162, 12, 12); // se dibuja el ojo izquierdo
  ellipse(147, 162, 12, 12);  // se dibuja el ojo derecho
  if(op==3)
  {
   drawSphere(); 
  }
}//Cierre de función para dibujar el robot


void drawLeftArm()
{
  pushMatrix();
  translate(112, 185);
    if(op==1)
    {
    rotate(radians(armAngle));
    rotateY(t);
    }
    t*=1.005;
  rect(-12, 0, 12, 37); // se dibuja el brazo
  popMatrix();
}//Cierre de brazo izq

void drawRightArm()
{
    if(op==3)
    {
      pushMatrix();
      translate(166, 185);
      rotate(radians(-armAngle2));
      rect(0, 0, 37, 12); // right arm
      popMatrix();
    }//Cirre de if
  
    else
    {
      pushMatrix();
      translate(166, 185);
      if(op==1)
    {
     rotate(radians(-armAngle));
     rotateY(t);
    }
    t*=1.005;
      rect(0, 0, 12, 37); // right arm
      popMatrix();
    }//Cierre de else
}//Cierre de brazo derecho

void drawPierna()
{
  pushMatrix();
  translate(140, 234);
    if(op==2)
    {
      rotate(radians(-armAngle));
    }
  
  rect(0, 0, 16, 50); //pierna
  popMatrix();
}//Cierre de pierna

void drawSphere()
{
  fill(255,0,0);
  stroke(255);
  pushMatrix();
translate(x, 180);
//translate(x, 180, -220);
  sphere(y);
  popMatrix();
  x+=15;
  y+=7;
}//Cierre de esfera