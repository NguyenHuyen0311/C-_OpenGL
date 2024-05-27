#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, Calpha= 360.0, C_hr_alpha=360.0; // Dieu chinh goc quay va huong cua vat the
GLboolean bRotate = false, fRotate= true, cRotate= true, xz_rotate=false,l_on=true; // Dieu khien che do quay va su hien dien cua nguon sang
const int width = 600; // chieu rong cua so
const int height = 800; // chieu cao cua so 

// ambient: as phan xa deu tu moi truong, specular: as phan xa theo huong cua nguon sang, diffuse: as phan xa deu tu mot nguon sang
GLboolean amb=true, spec=true, dif=true; 

// trang thai bat/tat cua nguon sang
bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;

double spt_cutoff=40.0; // cat bong cua nguon sang
GLfloat spot_direction[] = { 0.0, -1.0, 0.0 }; // Huong anh sang di xuong

float rot = 0; // goc quay

// Toa do mat nhin
GLfloat eyeX = 0;
GLfloat eyeY = 10;
GLfloat eyeZ = 13;

// Toa do huong nhin
GLfloat lookX = 0;
GLfloat lookY = 10;
GLfloat lookZ = 0;

// Mang 2 chieu moi hang la mot dinh cua hinh lap phuong
static GLfloat v_Cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

// Mang 2 chieu moi hang la mot mat phang cua hinh lap phuong
static GLubyte quadIndices[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

// Ham tinh toan va thiet lap vecto phap tuyen cho moi mat phang hinh lap phuong
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3) // Toa do 3 diem tren mot mat phang
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz); // Vecto phap tuyen cho mat phang
}

// Ham ve hinh lap phuong voi cac mau khac nhau
void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3) 
{
    GLfloat cube_no[] = {0, 0, 0, 1.0};
    GLfloat cube_amb[] = {colr1*0.3,colr2*0.3,colr3*0.3,1};
    GLfloat cube_dif[] = {colr1,colr2,colr3,1};
    GLfloat cube_spec[] = {1,1,1,1};
    GLfloat cube_sh[] = {10}; // Muc do phan chieu cua anh sang specular

    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);

	// Ve hinh lap phuong
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
    	// Thiet lap vecto phap tuyen cho mat phang hien tai
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        // Duyet qua tung dinh cua mat phang hinh lap phuong
		for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]); // Ve cac dinh do
        }

    }
    glEnd();
}

void chairBoss()
{
    glPushMatrix();
    glTranslatef(0.5,0.0,-7.0);
    glScalef(0.5,2.0,0.5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0,0.0,-7.0);
    glScalef(0.5,2.0,0.5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,0.0,-5.5);
    glScalef(0.5,2.0,0.5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0,0.0,-5.5);
    glScalef(0.5,2.0,0.5);
    cube(0.4, 0.4, 0.4);
    glPopMatrix();

	// Mat ghe
    glPushMatrix();
    glTranslatef(-1.0,2.0,-7.0);
    glScalef(2.0,2/6.0,2.0);
    cube(0.7, 0.7, 0.7);
    glPopMatrix();

	// Tua lung
    glPushMatrix();
    glTranslatef(-1.0,2.0,-7.0);
    glScalef(2.0,2.4,0.5);
    cube(0.7, 0.7, 0.7);
    glPopMatrix();
}

void chairStaff()
{
    //	Hang ghe phai
  	glPushMatrix(); 
  	glTranslatef(1.0,0.0,-3.0);
    glRotatef(90,0,1,0);
    chairBoss(); 
    glPopMatrix();

	glPushMatrix(); 
  	glTranslatef(1.0,0.0,0.0);
    glRotatef(90,0,1,0);
    chairBoss(); 
    glPopMatrix();
    
    glPushMatrix(); 
  	glTranslatef(1.0,0.0,3.0);
    glRotatef(90,0,1,0);
    chairBoss(); 
    glPopMatrix();
    
    //	Hang ghe trai
    glPushMatrix(); 
  	glTranslatef(-1.0,0.0,-3.0);
    glRotatef(-90,0,1,0);
    chairBoss(); 
    glPopMatrix();

	glPushMatrix(); 
  	glTranslatef(-1.0,0.0,0.0);
    glRotatef(-90,0,1,0);
    chairBoss(); 
    glPopMatrix();
    
    glPushMatrix(); 
  	glTranslatef(-1.0,0.0,3.0);
    glRotatef(-90,0,1,0);
    chairBoss(); 
    glPopMatrix();
}

void table()
{
    glPushMatrix();
    glTranslatef(3.0,0.0,-5.0);
    glScalef(0.5,3.0,0.5);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,0.0,-5.0);
    glScalef(0.5,3.0,0.5);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0,0.0,4.5);
    glScalef(0.5,3.0,0.5);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,0.0,4.5);
    glScalef(0.5,3.0,0.5);
    cube(0,0,0);
    glPopMatrix();

	// Mat ban	
    glPushMatrix();
    glScalef(7.5,0.5,11.0);
    glTranslatef(-0.5,6,-0.5);
    cube(0.8, 0.6, 0.4);
    glPopMatrix();
}

void fan()
{
    glPushMatrix();
    glRotatef(alpha,0.0,0.5,0.0); // Quay canh quat theo truc y
    
    // Mat quat
    glPushMatrix();
    glScalef(2,0.5,1.8);
    glTranslatef(-0.4,19.0,-0.4);
    cube(1.000, 1.000, 1.000);
    glPopMatrix();

	// Canh quat
    glPushMatrix();
    glScalef(2.0,0.07,1.8);
    glTranslatef(0.0,140,-0.3);
    cube(0.5, 0.8, 0.5);
    glPopMatrix();

	// Canh quat
    glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(5.0,0.07,1.8);
    glTranslatef(0.0,140,-0.3);
    cube(0.5, 0.8, 0.5);
    glPopMatrix();

	// Canh quat
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-6,0,0);
    glScalef(5.0,0.07,1.8);
    glTranslatef(0.0,140,-0.3);
    cube(0.5, 0.8, 0.5);
    glPopMatrix();

	// Canh quat
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(0,0,0);
    glScalef(5.0,0.07,1.8);
    glTranslatef(0.0,140,-0.3);
    cube(0.5, 0.8, 0.5);
    glPopMatrix();
    
    glPopMatrix();

	// Chan quat
    glPushMatrix();
    glScalef(0.5,5.0,0.5);
    glTranslatef(0.0,2.0,0.0);
    cube(0.5, 0.8, 0.5);
    glPopMatrix();
}

void fan_setup()
{
    glPushMatrix();
    glTranslatef(7.0,-0.8,4.0);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0,-0.8,4.0);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.0,-0.8,-9.0);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0,-0.8,-9.0);
    fan();
    glPopMatrix();
}

void window()
{
	// Mat kinh
    glPushMatrix();
    glScalef(0.1,10,10.0);
    glTranslatef(-140,0.3,-0.5);
    cube(0.5, 1, 1);
    glPopMatrix();

	// Thanh doc giua
    glPushMatrix();
    glScalef(0.1,10,0.1);
    glTranslatef(-139,0.3,0.0);
    cube(0, 0, 0);
    glPopMatrix();

	// Thanh ngang giua
    glPushMatrix();
    glScalef(0.1,0.1,10.0);
    glTranslatef(-139,75,-0.5);
    cube(0, 0, 0);
    glPopMatrix();

	// Thanh ngang tren
    glPushMatrix();
    glScalef(0.1,0.1,10.0);
    glTranslatef(-139,130,-0.5);
    cube(0, 0, 0);
    glPopMatrix();

	// Thanh ngang duoi
    glPushMatrix();
    glScalef(0.1,0.1,10.0);
    glTranslatef(-139,30,-0.5);
    cube(0, 0, 0);
    glPopMatrix();

	// Thanh doc phai
    glPushMatrix();
    glScalef(0.1,10,.1);
    glTranslatef(-139,0.3,-50);
    cube(0, 0, 0);
    glPopMatrix();

	// Thanh doc trai
    glPushMatrix();
    glScalef(0.1,10,.1);
    glTranslatef(-139,0.3,50);
    cube(0, 0, 0);
    glPopMatrix();
}

void window_setup()
{
    glPushMatrix();
    window();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
    window();
    glPopMatrix();
}

void projector()
{
	// Than may
    glPushMatrix();
    glScalef(2.0,0.7,1.8);
    glTranslatef(-0.43,15.0,-0.4);
    cube(1, 0, 0);
    glPopMatrix();

	// Chan may
    glPushMatrix();
    glScalef(0.5,3.4,0.5);
    glTranslatef(0.0,3.2,0.0);
    cube(0.392, 0.3, 0.929);
    glPopMatrix();

	// Ong kinh
    glPushMatrix();
    glScalef(0.68,0.68,0.68);
    glTranslatef(0.0,15.45,1.0);
    cube(1,0,1);
    glPopMatrix();

	// Mat kinh
    glPushMatrix();
    glScalef(0.60,0.60,0.60);
    glTranslatef(0.05,17.55,1.4);
    cube(0,0,0);
    glPopMatrix();
}

void projector_board()
{
    glPushMatrix();
    glScalef(12.0,7.0,0.1);
    glTranslatef(-0.5,0.8,130);
    cube(1, 1, 1);
    glPopMatrix();
}

void AC()
{
    glPushMatrix();
    glScalef(6.0,2.0,2.0);
    glTranslatef(-1.5,6.0,-7.5);
    cube(0.8, 0.8,0.8);
    glPopMatrix();
}

void oclock() {
	// Mat dong ho
    glPushMatrix();
    glTranslatef(1.0,8.0,-15);
    glScalef(3, 3, 0.1);
    cube(1, 1, 1);
    glPopMatrix();
    
    //kim gio
    glPushMatrix();
    glTranslatef(2.5,9.5,-14.88);
    glScalef(0.03, 0.5, 0.01);
    cube(0, 0, 0);
    glPopMatrix();

    //kim phut
    glPushMatrix();
    glTranslatef(2.57,9.5,-14.88);
    glScalef(0.03,1.3, 0.01);
    cube(0.392, 0.3, 0.929);
    glPopMatrix();
}

void door()
{
	// Canh cua
    glPushMatrix();
    glScalef(3.8,10,0.2);
    glTranslatef(2.2,0.0,-75);
    cube(0.9, 0.6, 0.8);
    glPopMatrix();

	// Nam cua
    glPushMatrix();
    glScalef(0.3,1.0,0.2);
    glTranslatef(28,4.5,-73);
    cube(0, 0, 0);
    glPopMatrix();
}

void floorWallsCeiling()
{
	// San nha
    glPushMatrix();
    glScalef(30,1,30);
    glTranslatef(-0.5,-1,-0.5);
    cube(1.0, 0.9, 0.6);
    glPopMatrix();

	// Tuong trai
    glPushMatrix();
    glTranslatef(15,7.5,0);
    glScalef(1,15,30);
    glTranslatef(-1,-0.5,-0.5);
    cube(1.0, 0.95, 0.7);
    glPopMatrix();

	// Tuong phai
    glPushMatrix();
    glTranslatef(-14,7.5,0);
    glScalef(1,15,30);
    glTranslatef(-1,-0.5,-0.5);
    cube(1.0, 0.95, 0.7);
    glPopMatrix();

	// Tuong truoc
    glPushMatrix();
    glTranslatef(0,7.5,15);
    glScalef(30,15,1);
    glTranslatef(-0.5,-0.5,-1);
    cube(1.0, 0.95, 0.7);
    glPopMatrix();

	// Tuong sau
    glPushMatrix();
    glTranslatef(0,7.5,15);
    glScalef(30,15,1);
    glTranslatef(-0.5,-0.5,-31);
    cube(1.0, 0.95, 0.7);
    glPopMatrix();

	// Tran nha
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(30,1,30);
    glTranslatef(-0.5,-1,-0.5);
    cube(1.0, 0.9, 0.6);
    glPopMatrix();
}

void bulb() {
    if(l_on3) {
    	// ambient: mau phan xa deu tu moi truong, specular: mau phan xa theo huong cua nguon sang, diffuse: mau phan xa deu tu mot nguon sang
        GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
        GLfloat mat_shininess[] = { 100.0f }; // Do bong

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    } else {
        GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f }; // M u ph?n x? ph?n x?
        GLfloat mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f }; // M u ph?n x? th?p
        GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f }; // M u ph?n x? cao
        GLfloat mat_shininess[] = { 100.0f }; // B?c s ng b ng

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    }
    
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(0.0, 28.0, -5.0);
    glutSolidSphere(1.0f, 40, 40); // Ve hinh cau
    glPopMatrix();
}


void light()
{
	// Mau sac anh sang duoc phan xa qua phan xa ambient, diffuse, specular
    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat l_dif[] = {0.961, 0.871, 0.702};
    GLfloat l_spec[] = {0.2,0.2,0.2,1};
    
    // Khi khong bat nguon sang
    GLfloat l_no[] = {0, 0, 0, 1.0}; 
    
    // Vi tri 3 nguon sang
    GLfloat l_pos1[] = {-20,20,20,1.0};
    GLfloat l_pos2[] = {44,30,-5,1.0};
    GLfloat l_pos3[] = {0,60,0,1.0};

	// Bat cac nguon sang
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);

    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);

    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
        
        if(spec==true)
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
        }
        
        // Cai dat vi tri cua nguon sang 3        
        glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

		// Cai dat huong anh sang cua nguon sang 3
	    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	    
	    // Cai dat goc cat cua nguon sang 3
	    GLfloat spt_ct[] = {spt_cutoff};
	    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
	    
	    // Cai dat mui phu cua nguon sang 3
	    GLfloat spot_exponent = 5.0;
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spot_exponent);

    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

    glRotatef(rot, 0,1,0); // Quay canh quan theo truc y mot góc rot
    light();
    fan_setup();
	chairBoss();
	chairStaff();
	table();
    floorWallsCeiling();
    window_setup();
    projector();
    AC();
    oclock();
    projector_board();
    bulb();
    door();
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'd':
        rot++;
        break;

    case 'a':
        rot--;
        break;

    case 'w':
        eyeY++;
        break;

    case 's':
        eyeY--;
        break;

    case 'z':
        eyeX=0;
        eyeZ++;
        lookZ++;
        break;

    case 'x':
        eyeZ--;
        break;

    case '1':
        l_on1=!l_on1;
        break;
    case '2':
        l_on2=!l_on2;
        break;
    case '3':
        l_on3=!l_on3;
        break;
     case '4':
        l_on1 = false;
        l_on2 = false;
        l_on3 = false;
        break;
    case '5':
        l_on1 = true;
        l_on2 = true;
        l_on3 = true;
        break;
    // Phim tat de thay doi huong chieu cua nguon sang
    case 'f':
        spot_direction[0] += 0.1; // tang hoanh do cua huong chieu len 0.1
        break;
    case 'g':
        spot_direction[0] -= 0.1; // giam hoanh do cua huong chieu xuong 0.1
        break;
    case 'h':
        spot_direction[1] += 0.1; // tang tung do cua huong chieu len 0.1
        break;
    case 'j':
        spot_direction[1] -= 0.1; // giam tung do cua huong chieu xuong 0.1
        break;
    case 'k':
        spot_direction[2] += 0.1; // tang sau do cua huong chieu len 0.1
        break;
    case 'l':
        spot_direction[2] -= 0.1; // giam sau do cua huong chieu xuong 0.1
        break;
    }
}

void animate()
{
    if (bRotate == true) // thuc hien xoay
    {
        theta += 0.1; // thay doi goc quay vat the
        // Neu theta vuot quá 360 se dua ve khoang giá tri tu 0 den 360 bang cach lay phan du cua theta khi chia cho 360.
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0); 
    }

    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    glutPostRedisplay();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(height, width);
    glutCreateWindow("Meeting Room Group 6");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}


