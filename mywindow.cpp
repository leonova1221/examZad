/*
 * ExampleWindow.cc
 *
 *  Created on: 19 окт. 2020 г.
 *      Author: unyuu
 */

#include <cmath>

static constexpr double Pi = acos(-1.);

#include "mywindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>


MyWindow::MyWindow(int width, int height)
: Window(800, 600)
{
    _angle = 0.;
    _eye_level = 0.;
}

/*
 *	Цвета
 */
static const float s_material_red[4]     { 1.f, 0.f, 0.f, 1.f };
static const float s_material_green[4]   { 0.f, 1.f, 0.f, 1.f };
static const float s_material_blue[4]    { 0.f, 0.f, 1.f, 1.f };
static const float s_material_cyan[4]    { 0.f, 1.f, 1.f, 1.f };
static const float s_material_magenta[4] { 1.f, 0.f, 1.f, 1.f };
static const float s_material_yellow[4]  { 1.f, 1.f, 0.f, 1.f };

/* setup
 *
 * glClearColor - устанавлием цвет по умолчанию
 * glMatrixMode - режим матрицы видового преобразования
 * gluPerspective - перспективное проециование
 *
 */
void MyWindow::setup()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(0.15f, 0.15f, 0.4f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45., double(width()) / double(height()), 0.01, 20.0);
    glMatrixMode(GL_MODELVIEW);
}


/* render
 *
 * gluLookAt - параметры камеры (координаты, вектор, ось Y)
 * glRotated - вращение камеры
 * glBegin - сообщение о начале рисования
 * glEnd - конец отрисовки
 */
void MyWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
            5., 5., 5. * _eye_level,
            0., 0., 0.,
            0., 0., 1.);

    glRotated(_angle, 1., 0., 1.);

    glBegin(GL_QUADS);


    glNormal3d(  0.,  1.,  0.);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_green);
    glVertex3d( -1.,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x,  1. + _y, -1.);
    glVertex3d( -1.,  1. + _y, -1.);

    glNormal3d(  0., -1.,  0.);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_green);
    glVertex3d(  1. + _x, -1.,  1. + _z);
    glVertex3d( -1., -1.,  1. + _z);
    glVertex3d( -1., -1., -1.);
    glVertex3d(  1. + _x, -1., -1.);

    glNormal3d(  0.,  0.,  1.);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_green);
    glVertex3d( -1.,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x, -1.,  1. + _z);
    glVertex3d( -1., -1.,  1. + _z);

    glNormal3d(  0.,  0., -1.);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_green);
    glVertex3d(  1. + _x,  1. + _y, -1);
    glVertex3d( -1.,  1. + _y, -1.);
    glVertex3d( -1., -1., -1.);
    glVertex3d(  1. + _x, -1., -1.);

    glEnd();

    //glBegin(GL_SQUARE_NV);
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
    glVertex3d( -1.,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x,  1. + _y,  1. + _z);
    glVertex3d(  1. + _x,  0.,  2. + _z);
    glVertex3d( -1.,  0.,  2. + _z);

    glVertex3d(  1. + _x,  0., 2. + _z);
    glVertex3d( -1.,  0., 2. + _z);
    glVertex3d( -1., -1., 1. + _z);
    glVertex3d(  1. + _x, -1., 1. + _z);

    glEnd();



}
/*
 * E - влево
 * R - Вправо
 *
 * Q - увеличить дом по оси x
 * A - увеличить дом по оси y
 * Z - увеличить дом по оси z
 *
 * W - уменьшить дом по оси x
 * S - уменьшить дом по оси y
 * X - уменьшить дом по оси z
 *
 */
void MyWindow::handle_keys(const Uint8 *keys)
{
    if(keys[SDL_SCANCODE_E]) _angle+=1;
    if(keys[SDL_SCANCODE_R]) _angle-=1;
    if(keys[SDL_SCANCODE_Q]) _x += 0.1;
    if(keys[SDL_SCANCODE_A]) _y += 0.1;
    if(keys[SDL_SCANCODE_Z]) _z += 0.1;
    if(keys[SDL_SCANCODE_W]) _x -= 0.1;
    if(keys[SDL_SCANCODE_S]) _y -= 0.1;
    if(keys[SDL_SCANCODE_X]) _z -= 0.1;

}
/*
 * handle_logic - расчёт поворота камеры
 */
void MyWindow::handle_logic()
{
    //_angle += 1.;
    if (_angle >= 360.)
        _angle -= 360.;

    _eye_level = cos(_angle / 180. * Pi);
}
