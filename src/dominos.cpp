/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

/*! \file
   \brief dominoes implementaton
*/

#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  //!Note: All those comments beginning by '<' are the ones succeeding the members, hence the syntax asks us for '<'.
  //!We have set "HIDE_IN_BODY_DOCS = NO" so that the comments inside namespace cs296 are extracted and displayed in the documentation.
  /*! Constructor function for dominos */
  dominos_t::dominos_t()
  {
    //! Ground
    b2Body* b1; //!<'b2Body* b1' Declares a pointer pointing to a body for the ground
    {
      b2EdgeShape shape; //!<'b2EdgeShape shape' creates an edge shape
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f)); /*!<'shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f))' draws an edge between the given vertices and saves it in shape*/
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      b1 = m_world->CreateBody(&bd); /*!<'b1 = m_world->CreateBody(&bd)' creates a body with the above definition and stores it in the location pointed by b1*/
      b1->CreateFixture(&shape, 0.0f); /*!<'b1->CreateFixture(&shape, 0.0f)' attaches the shape to the body by creating a fixture of density 0.0f */
    }
      
    //!Top horizontal shelf
    {
      b2PolygonShape shape; //!<'b2PolygonShape shape' declares a polygon shape for the shelf
      shape.SetAsBox(23.0f, 0.25f); //!<'shape.SetAsBox(23.0f, 0.25f)' creates a box with width 46.0f and height 0.50f
      b2BodyDef bd; //!<'b2BodyDef bd' declares a body definition
      bd.position.Set(0.0f, 32.0f); //!<'bd.position.Set(0.0f,32.0f)' sets the position of the body at (0.0f,32.0f)
      b2Body* ground = m_world->CreateBody(&bd); //!<'b2Body* ground = m_world->CreateBody(&bd)' creates a body with the body definition bd
      ground->CreateFixture(&shape, 0.0f); /*!<'ground->CreateFixture(&shape, 0.0f)' attaches the shape to the body by creating a fixture of density 0.0f */
    }
    
    //!The cannon shot
    {
    	b2Body* spherebody; //!<'b2Body* spherebody' Declares a pointer pointing to the body of the cannon shot
      
      b2CircleShape circle; //!<'b2CircleShape circle' Declares a circular shape for the cannon
      circle.m_radius = 1.0; //!<'circle.m_radius = 1.0' Declares the radius
      
      b2FixtureDef ballfd; /*!<'b2FixtureDef ballfd' creates a fixture and in the subsequent lines we attach the shape, density, friction and restitution to the fixture*/
      ballfd.shape=&circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.02f;
      
      b2BodyDef ballbd; //!<'b2BodyDef ballbd' Declares a body definition
      ballbd.type = b2_dynamicBody; //!<'ballbd.type = b2_dynamicBody' Declares the body type as dynamic
      ballbd.position.Set(3.0f, 35.0f); //!<'ballbd.position.Set(3.0f, 35.0f)' sets the initial position of the body
      spherebody = m_world->CreateBody(&ballbd); /*!<'spherebody = m_world->CreateBody(&ballbd)' creates a body with the above body definition ballbd*/
      spherebody->CreateFixture(&ballfd); //!<'spherebody->CreateFixture(&ballfd)'Associates the fixture with the body
      spherebody->SetLinearVelocity(b2Vec2(17.0f,15.0f));/*!<'spherebody->SetLinearVelocity(b2Vec2(17.0f,15.0f))' gives an initial velocity to the body in the defined direction*/
    }
    
    //!The cannon
    {
    //!The Wheel of the cannon
    	b2BodyDef cannon; //!<'b2BodyDef cannon' Declares a body definition for the cannon
    	cannon.position.Set(0.0f,33.0f);//!<'cannon.position.Set(0.0f,33.0f)' sets the initial position of the body
    	cannon.type=b2_dynamicBody;//!<'cannon.type=b2_dynamicBody' Declares the body type as dynamic
    	
    	b2FixtureDef fd1; /*!<'b2FixtureDef fd1' creates a fixture and in the subsequent lines we attach the shape, density, friction to the fixture*/
    	b2CircleShape circle; //!<'b2CircleShape circle' Declares a circular shape for the cannon
    	circle.m_radius = 1.5;//!<'circle.m_radius = 1.5' Declares the radius
    	
    	fd1.shape=&circle;
    	fd1.density=2.5f;
    	fd1.friction=1.0f;
    	
    	//!The upper edge of the cannon
    	b2FixtureDef fd2; /*!<'b2FixtureDef fd2' creates a fixture and in the subsequent lines we attach the shape, density, friction to the fixture*/
    	b2PolygonShape shape1; //!<'b2PolygonShape shape1' Declares a Polygon shape for the body
     shape1.SetAsBox(4.0f, 0.25f,b2Vec2(0.7f,3.5f),3.14/4); /*!<'shape1.SetAsBox(4.0f, 0.25f,b2Vec2(0.7f,3.5f),3.14/4)' creates a box with width 8.0f and height 0.50f at an angle 3.14/4 at the specified position vector*/
     fd2.shape=&shape1;
     fd2.density=15.0f;
     fd2.friction=1.0f;
      
     //!The lower edge of the cannon is created similarly as the above edge with the modified coordinates
     b2FixtureDef fd3;
    	b2PolygonShape shape2;
     shape2.SetAsBox(3.5f, 0.25f,b2Vec2(4.0f,2.0f),3.14/4);
     fd3.shape=&shape2;
     fd3.density=15.0f;
     fd3.friction=1.0f;
      
     b2Body* cnn = m_world->CreateBody(&cannon); //!<'b2Body* cnn = m_world->CreateBody(&cannon)' Declares a body
     cnn->CreateFixture(&fd1); //!<'cnn->CreateFixture(&fd1)' The body is attached with the fixture fd1
     cnn->CreateFixture(&fd2); //!<'cnn->CreateFixture(&fd1)' The body is attached with the fixture fd2
     cnn->CreateFixture(&fd3); //!<'cnn->CreateFixture(&fd1)' The body is attached with the fixture fd3
     cnn->SetLinearVelocity(b2Vec2(-5.0f,0.0f)); //!<'' The body is given an initial velocity in the declared direction
    }
     
    //!The ball hit by the recoil 
    {
	 b2Body* spherebody; //!<'b2Body* spherebody' Declares a pointer to the body for the ball
      
      b2CircleShape circle; //!<'b2CircleShape circle' Declares a circular shape for the ball
      circle.m_radius = 1.0;//!<'circle.m_radius = 1.0' Declares a radius for the circle
      
      b2FixtureDef ballfd; /*!<'b2FixtureDef ballfd' creates a fixture and in the subsequent lines we attach the shape, density, friction and restitution to the fixture*/
      ballfd.shape=&circle;
      ballfd.density = 9.0f;
      ballfd.friction = 0.1f;
      ballfd.restitution = 0.3f;
      
      b2BodyDef ballbd; //!<'b2BodyDef ballbd' Declares a body definition
      ballbd.type = b2_dynamicBody; //!<'ballbd.type = b2_dynamicBody' Declares the body type as dynamic
      ballbd.position.Set(-4.5f, 33.0f); //!<'ballbd.position.Set(-4.5f, 33.0f)' sets the initial position of the body
      spherebody = m_world->CreateBody(&ballbd); //!<'' creates a body with body definition ballbd
      spherebody->CreateFixture(&ballfd); //!<'spherebody->CreateFixture(&ballfd)' Attaches the fixture defined above to the body
	 }
    	  
    //!Right side's angular shelf
    {
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the shelf
      shape.SetAsBox(5.0f, 0.25f, b2Vec2(55.f,30.f), 3.14/18.0f); /*!<'shape.SetAsBox(5.0f, 0.25f, b2Vec2(55.f,30.f), 3.14/18.0f)' creates a box with width 10.0f and height 0.50f at an angle of 3.14/18 at the specified position vector*/
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
	 b2Body* shelf = m_world->CreateBody(&bd);//!<'b2Body* shelf = m_world->CreateBody(&bd)' Creates a body with body definition bd
      shelf->CreateFixture(&shape, 0.0f); /*!<'shelf->CreateFixture(&shape, 0.0f)' attaches the shape to the body by creating a fixture of density 0.0f*/
    }

    //!Right side's vertical shelf
    {
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the shelf
      shape.SetAsBox(2.0f, 0.25f); /*!<'shape.SetAsBox(2.0f, 0.25f)'  creates a box with width 4.0f and height 0.50f*/
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      bd.angle = (3.14/2); //!<'bd.angle = (3.14/2)' Sets the angle of the body definition
      bd.position.Set(60.0f, 33.0f); //!<'bd.position.Set(60.0f, 33.0f)' Sets the position of the body definition
      b2Body* ground = m_world->CreateBody(&bd); /*!<'b2Body* ground = m_world->CreateBody(&bd)' Creates a pointer to the body of the vertical shelf with body definition as bd*/
      ground->CreateFixture(&shape, 0.0f); /*!<'ground->CreateFixture(&shape, 0.0f)' Attaches the fixture defined above to the body*/
    }
    
    //!Right horizontal shelf
    {
    	b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
    	bd.position.Set(45.0f,28.0f); //!<'bd.position.Set(45.0f,28.0f)' Sets the position of the body definition
    	b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the shelf
    	shape.SetAsBox(3.0f,0.25f,b2Vec2(0.0f,0.0f),0); /*!<'shape.SetAsBox(3.0f,0.25f,b2Vec2(0.0f,0.0f),0)' creates a box with width 6.0f and height 0.50f*/
    	b2Body* shelf = m_world->CreateBody(&bd); /*!<'b2Body* shelf = m_world->CreateBody(&bd)' Creates a pointer to the body of the horizontal shelf with body definition as bd*/
    	shelf->CreateFixture(&shape,0.0f); /*!<'ground->CreateFixture(&shape, 0.0f)' Attaches the fixture defined above to the body*/
    }

    //!Right revolving part - 1
    {
      //!The actual rotating body
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the shelf
      shape.SetAsBox(0.2f, 1.5f); /*!<'shape.SetAsBox(0.2f, 1.5f)' creates a box with width 0.4f and height 3.f*/
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      bd.position.Set(41.75f, 26.5f); //!<'bd.position.Set(41.75f, 26.5f)' Sets the position of the body definition
      bd.type = b2_dynamicBody; //!<'bd.type = b2_dynamicBody' Sets the type to dynamic
      b2Body* body = m_world->CreateBody(&bd); /*!<'b2Body* body = m_world->CreateBody(&bd)' creates a body with the above body definition bd*/
      b2FixtureDef *fd = new b2FixtureDef; /*!<'b2FixtureDef *fd = new b2FixtureDef' creates a fixture and in the subsequent lines we attach the shape, density to the fixture*/
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd); /*!<'body->CreateFixture(fd)' Attaches the fixture defined above to the body*/

      //!The hinge
	       
      b2PolygonShape shape2; //!<'b2PolygonShape shape2' Declares a polygon shape for the hinge 
      shape2.SetAsBox(0.2f, 2.0f);/*<'shape2.SetAsBox(0.2f, 2.0f)' creates a box with width 0.4f and height 4.f*/
      b2BodyDef bd2; //!<'b2BodyDef bd2' Declares a body definition 
      bd2.position.Set(41.75f, 28.f); //!<'bd2.position.Set(41.75f, 28.f)' Sets the position of the body definition
      b2Body* body2 = m_world->CreateBody(&bd2); /*!<'b2Body* body2 = m_world->CreateBody(&bd2)' creates a body with the above body definition bd2*/
 
      b2RevoluteJointDef jointDef; //!<'b2RevoluteJointDef jointDef' the joint around which the plank rotates
      jointDef.bodyA = body; //!<'jointDef.bodyA = body' Defines one of the body that needs to be anchored
      jointDef.bodyB = body2; //!<'jointDef.bodyB = body2' Defines the other body that needs to be anchored
      jointDef.localAnchorA.Set(0.0,-1.5f); /*!<'jointDef.localAnchorA.Set(0.0,-1.5f)' Sets the point of anchor in the first body (The coordinates are with respect to the centre of mass of the body) */
      jointDef.localAnchorB.Set(0,0); /*!<'jointDef.localAnchorB.Set(0,0)' Sets the point of anchor in the first body (The coordinates are with respect to the centre of mass of the body) */
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);  
    }
    
    //!Right horizontal shelf
    {
      b2BodyDef bd;//!<'b2BodyDef bd' Declares a body definition 
      bd.position.Set(38.0f,23.0f); //!<'bd.position.Set(38.0f,23.0f)' Sets the position of the body definition
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the hinge
      shape.SetAsBox(3.0f,0.25f,b2Vec2(0.0f,0.0f),0); /*!<'shape.SetAsBox(3.0f,0.25f,b2Vec2(0.0f,0.0f),0)' creates a box with width 6.f and height 0.5f, centre of the box as (0,0) and 0 radian rotation of the box*/
      b2Body* shelf = m_world->CreateBody(&bd); /*!<'b2Body* shelf = m_world->CreateBody(&bd)' Creates a pointer to the body of shelf with bd as the body definition*/
      shelf->CreateFixture(&shape,0.0f); /*!<'shelf->CreateFixture(&shape,0.0f)'  Attaches the fixture defined above to the body*/

      b2BodyDef bd2; //!<'b2BodyDef bd2' Declares a body definition
      bd2.position.Set(35.0f,24.f); //!<'bd2.position.Set(35.0f,24.f)' Sets the position of the body definition
      b2PolygonShape shape1; //!<'b2PolygonShape shape1' Declares a polygon shape
      shape1.SetAsBox(0.2f,1.0f); /*!<'shape1.SetAsBox(0.2f,1.0f)' creates a box with width 0.4f and height 2.f*/
      b2FixtureDef fd; /*!<'b2FixtureDef fd' creates a fixture and in the subsequent lines we attach the shape, restitution to the fixture*/
      fd.shape=&shape1;
      fd.restitution=0.01f;
      b2Body* obstruction = m_world->CreateBody(&bd2); /*!<'b2Body* obstruction = m_world->CreateBody(&bd2)' Creates a pointer to the body of the obstruction with bd2 as the body definition*/
      obstruction->CreateFixture(&shape1,0.0f); /*!<'obstruction->CreateFixture(&shape1,0.0f)' Attaches a fixture with shape1 and density 0 to the obstruction body*/
    }

    //!Right revolving part - 2
    {
      //!The actual rotating body
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the shelf
      shape.SetAsBox(0.2f, 1.5f); /*!<'shape.SetAsBox(0.2f, 1.5f)' creates a box with width 0.4f and height 3.f*/
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      bd.position.Set(41.25f, 21.5f); //!<'bd.position.Set(41.25f, 21.5f)'  Sets the position of the body definition
      bd.type = b2_dynamicBody; //!<'bd.type = b2_dynamicBody' Sets the type to dynamic
      b2Body* body = m_world->CreateBody(&bd); /*!<'b2Body* body = m_world->CreateBody(&bd)' creates a body with the above body definition bd*/
      b2FixtureDef *fd = new b2FixtureDef; /*!<'b2FixtureDef *fd = new b2FixtureDef' creates a fixture and in the subsequent lines we attach the shape, density to the fixture*/
      fd->density = 1.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd); /*!<'body->CreateFixture(fd)' Attaches the fixture defined above to the body*/
      
      //!The hinge
      b2PolygonShape shape2; //!<'b2PolygonShape shape2' Declares a polygon shape for the hinge 
      shape2.SetAsBox(0.2f, 2.0f); /*!<'shape2.SetAsBox(0.2f, 2.0f)' creates a box with width 0.4f and height 4.f*/
      b2BodyDef bd2; //!<'b2BodyDef bd2' Declares a body definition 
      bd2.position.Set(41.25f, 23.f); //!<'bd2.position.Set(41.25f, 23.f)' Sets the position of the body definition
      b2Body* body2 = m_world->CreateBody(&bd2); /*!<'b2Body* body2 = m_world->CreateBody(&bd2)' creates a body with the above body definition bd2*/
 
      b2RevoluteJointDef jointDef; //!<'b2RevoluteJointDef jointDef' the joint around which the plank rotates
      jointDef.bodyA = body; //!<'jointDef.bodyA = body' Defines one of the body that needs to be anchored
      jointDef.bodyB = body2; //!<'jointDef.bodyB = body2' Defines the other body that needs to be anchored
      jointDef.localAnchorA.Set(0.0,-1.5f); /*!<'jointDef.localAnchorA.Set(0.0,-1.5f)' Sets the point of anchor in the first body (The coordinates are with respect to the centre of mass of the body) */
      jointDef.localAnchorB.Set(0,0); /*!<'jointDef.localAnchorB.Set(0,0)' Sets the point of anchor in the first body (The coordinates are with respect to the centre of mass of the body) */
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //!Right horizontal shelf
    //!< It is defined in a similar manner as being defined above with the appropriate coordinates
    {
      b2BodyDef bd;
      bd.position.Set(37.0f,18.0f);
      b2PolygonShape shape;
      shape.SetAsBox(5.0f,0.25f,b2Vec2(0.0f,0.0f),0);
      b2Body* shelf = m_world->CreateBody(&bd);
      shelf->CreateFixture(&shape,0.0f);
    }

    //!Right ball
    {
      b2Body* spherebody; //!<'b2Body* spherebody' Declares a pointer to the body of the ball
      b2CircleShape shape; //!<'b2CircleShape shape' Declares a circular shape for the ball
      shape.m_radius=1.0f; //!<'shape.m_radius=1.0f' Declares the radius of the ball
      b2FixtureDef fd; /*!<'b2FixtureDef fd' creates a fixture and in the subsequent lines we attach the shape, friction, restitution to the fixture*/
      fd.shape=&shape; 
      fd.friction=0.0f;
      fd.restitution=1.f;
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      bd.position.Set(40.5f,18.5f); //!<'bd.position.Set(40.5f,18.5f)'  Sets the position of the body definition
      bd.type=b2_dynamicBody; //!<'bd.type=b2_dynamicBody' Sets the body type to be dynamic
      spherebody=m_world->CreateBody(&bd); /*!<'spherebody=m_world->CreateBody(&bd)' creates a body with the above body definition bd*/
      spherebody->CreateFixture(&fd); /*!<'spherebody->CreateFixture(&fd)' Attaches the above defined fixture to the body*/
    }
    
    
    
     //!Right side's horizontal shelf
     //!< It is defined in a similar manner as being defined above with the appropriate coordinates
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f);
      b2BodyDef bd;
      bd.position.Set(25.0f, 16.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
   //!Dominos
    {
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the dominos
      shape.SetAsBox(0.2f, 1.0f); //!<'shape.SetAsBox(0.2f, 1.0f)' creates a box with width 0.4f and height 2.f
      b2FixtureDef fd; /*!<'b2FixtureDef fd' creates a fixture and in the subsequent lines we attach the shape, density, friction to the fixture*/
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      for (int i = 0; i < 7; ++i) //!< Now creating 7 dominos and placing them appropriately
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(21.5f + 1.0f * i, 17.5f);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}
    }
      
    //!Another horizontal shelf towards the right the bottom one
    //!< It is defined in a similar manner as being defined above with the appropriate coordinates
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(20.f,14.0f), 0.0f);
      b2BodyDef bd;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //!Ball hit by the dominoes
    //!< It is defined in the same manner as other balls defined above with no initial velocity and placed appropriately
    {
      b2Body* spherebody;
      
      b2CircleShape circle;
      circle.m_radius = 1.0;
      
      b2FixtureDef ballfd;
      ballfd.shape=&circle;
      ballfd.density = 13.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.5f;
      
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(18.5f, 14.5f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
    }
	
	//!The weight balance system
	{
	      //!The triangle wedge
	      b2Body* sbody; //!<'b2Body* sbody' Creates a pointer to the body of the wedge
	      b2PolygonShape poly; //!<'b2PolygonShape poly' Creates a polygon shape for the wedge
	      b2Vec2 vertices[3]; /*!<'b2Vec2 vertices[3]' Create a vector containing the coordinates of the three points containing the wedge and subsequently initializing it*/
	      vertices[0].Set(-2,0);
	      vertices[1].Set(2,0);
	      vertices[2].Set(0,4.0);
	      poly.Set(vertices, 3); //!<'poly.Set(vertices, 3)' Sets the vertices of the wedge with above defined coordinate vector
	      b2FixtureDef wedgefd; /*!<'b2FixtureDef wedgefd' creates a fixture and in the subsequent lines we attach the shape, density, friction, restitution to the fixture*/ 
	      wedgefd.shape = &poly;
	      wedgefd.density = 0.0f;
	      wedgefd.friction = 0.0f;
	      wedgefd.restitution = 0.0f;
	      b2BodyDef wedgebd; //!<'b2BodyDef wedgebd' Declares a body definition for the wedge
	      wedgebd.position.Set(5.0f, 0.0f); //!<'wedgebd.position.Set(5.0f, 0.0f)' Sets the position of the body definition
	      sbody = m_world->CreateBody(&wedgebd); /*!<'sbody = m_world->CreateBody(&wedgebd)' creates a body with the above body definition wedgebd*/
	      sbody->CreateFixture(&wedgefd); /*!<'sbody->CreateFixture(&wedgefd)' Attaches the fixture with the body*/
	      
              /*!<Now, we design the frame of the weight balance system lying on the wedge using 7 polygon shaped fixtures appropriately placed and attaching to a body of dynamic type*/
              /*!< Then we anchor the frame with the wedge at the tip of the wedge*/
              b2BodyDef bd;
              bd.position.Set(5.0f,4.0f);
              bd.type=b2_dynamicBody;
              
              b2FixtureDef *fd1 = new b2FixtureDef;
              fd1->shape = new b2PolygonShape;
              b2PolygonShape shape;
      	      shape.SetAsBox(6.0f, 0.25f);
      	      fd1->density=1.f;
      	      fd1->shape=&shape;
      	      fd1->restitution=0.0;
              
              b2FixtureDef *fd2 = new b2FixtureDef;
              fd2->shape = new b2PolygonShape;
              b2PolygonShape shape2;
      	      shape2.SetAsBox(0.25f, 2.0f,b2Vec2(5.5f,2.0f),0);
      	      fd2->shape=&shape2;
      	      fd2->density=0.0;
      	      fd2->restitution=0.0;

      	      b2FixtureDef *fd3 = new b2FixtureDef;
      	      fd3->shape = new b2PolygonShape;
      	      b2PolygonShape shape3;
      	      shape3.SetAsBox(2,0.2,b2Vec2(5.5f,4.0f),0);
      	      fd3->shape=&shape3;
      	      fd3->density=0.0;
      	      fd3->restitution=0.0;

      	      b2FixtureDef *fd4 = new b2FixtureDef;
      	      fd4->shape = new b2PolygonShape;
      	      b2PolygonShape shape4;
      	      shape4.SetAsBox(0.2,2,b2Vec2(3.75f,5.75f),0);
      	      fd4->shape=&shape4;
      	      fd4->density=0.0;
      	      fd4->restitution=0.0;

      	      b2FixtureDef *fd5 = new b2FixtureDef;
      	      fd5->shape = new b2PolygonShape;
      	      b2PolygonShape shape5;
      	      shape5.SetAsBox(0.2,2,b2Vec2(7.25f,5.75f),0);
      	      fd5->shape=&shape5;
      	      fd5->density=0.0;
      	      fd5->restitution=0.0;

      	      b2FixtureDef *fd6 = new b2FixtureDef;
      	      fd6->shape = new b2PolygonShape;
      	      b2PolygonShape shape6;
      	      shape6.SetAsBox(0.25f, 4.0f,b2Vec2(-5.5f,3.5f),0);
      	      fd6->shape=&shape6;
      	      fd6->density=0.0;
      	      fd6->restitution=0.0;

      	      b2FixtureDef *fd7 = new b2FixtureDef;
      	      fd7->shape = new b2PolygonShape;
      	      b2PolygonShape shape7;
      	      shape7.SetAsBox(2.0f, 0.2f,b2Vec2(-5.5f,7.0f),0);
      	      fd7->shape=&shape7;
      	      fd7->density=0.0;
              fd7->restitution=0.0;
      	      
      	      b2Body* body = m_world->CreateBody(&bd);
      	      body->CreateFixture(fd1);
      	      body->CreateFixture(fd2);
      	      body->CreateFixture(fd3);
      	      body->CreateFixture(fd4);
      	      body->CreateFixture(fd5);
      	      body->CreateFixture(fd6);
      	      body->CreateFixture(fd7);
      	      
      	      b2RevoluteJointDef jd;
              b2Vec2 anchor;
              anchor.Set(5.0f, 4.0f);
              jd.Initialize(body, sbody, anchor);
              m_world->CreateJoint(&jd);
      	      
              
              
	  }
	
    
    
    //!The left pulley system
    
    {
      b2BodyDef *bd = new b2BodyDef; //!<'b2BodyDef *bd = new b2BodyDef' Creates a body definition
      bd->type = b2_dynamicBody;//!<'bd->type = b2_dynamicBody' Body definition is set as dynamic type
      bd->position.Set(-22,23); //!<'bd->position.Set(-22,23)' Sets the position in the body definiiton
      bd->fixedRotation = true; //!<'bd->fixedRotation = true' Prevents the body from rotating
      
      //!The open box on the left-hand side of the pulley
      b2FixtureDef *fd1 = new b2FixtureDef; /*!<'b2FixtureDef *fd1 = new b2FixtureDef'creates a fixture and in the subsequent lines we attach the shape, density, friction, restitution to the fixture*/
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1; //!<'' Creates a polygon shape
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-13.9f), 0); /*!<'bs1.SetAsBox(2,0.2, b2Vec2(0.f,-13.9f), 0)' creates a box with width 4.f and height 0.4f, centre of the box as (0,-13.9f) and 0 radian rotation of the box*/
      fd1->shape = &bs1; //!<Similarly we create 2 more polygon shaped fixtrues
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,-12.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,-12.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd); /*!<'b2Body* box1 = m_world->CreateBody(bd)' Creates a pointer to the open box with bd as body definition and subsequently attach it to the fixtures of the three edges of the open box*/
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //!The Toothbrush Frame
      b2FixtureDef *fd4 = new b2FixtureDef; /*!<'b2FixtureDef *fd4 = new b2FixtureDef'creates a fixture and in the subsequent lines we attach the shape, density, friction, restitution to the fixture*/
      fd4->density = 18;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape; 
      b2PolygonShape bs4; //!<'fd4->shape = new b2PolygonShape' Creates a polygon shape for the brush
      bs4.SetAsBox(3.5,0.2, b2Vec2(0.f,-13.9f), 0); /*!<'bs4.SetAsBox(3.5,0.2, b2Vec2(0.f,-13.9f), 0)' creates a box with width 7.f and height 0.4f, centre of the box as (0,-13.9f) and 0 radian rotation of the box*/
      fd4->shape = &bs4; //!<'fd4->shape = &bs4' Assigns &bs4 to the shape of the fixture

	 //!The Bristles of the brush
	 //!<We similarly create the brisltes of the brush using polygon shaped fixtures fd5 fd6
      b2FixtureDef fd5;
      fd5.density = 0.0f;
      b2PolygonShape shaped;
      shaped.SetAsBox(0.1f,0.6f,b2Vec2(3.5f,-13.4f), 0);
      fd5.shape=&shaped;

      b2FixtureDef fd6;
      fd6.density = 0.0f;
      b2PolygonShape shaped1;
      shaped1.SetAsBox(0.1f,0.6f,b2Vec2(2.5f,-13.4f), 0);
      fd6.shape=&shaped1;
	 
	 //!The Toothbrush
      bd->position.Set(-5,15); //!<'bd->position.Set(-5,15)' Sets the position of the toothbrush body
      fd1->density = 30.0; //!<'fd1->density = 30.0' Sets the density of the fixture definition fd1
      bd->bullet=false;  
      b2Body* box2 = m_world->CreateBody(bd); /*!<'b2Body* box2 = m_world->CreateBody(bd)' creates a body with the above body definition bd*/
      box2->CreateFixture(fd4); //!<'box2->CreateFixture(fd4)' Attaches fixture fd4 to the body of toothbrush
      box2->CreateFixture(&fd5); //!<'box2->CreateFixture(fd5)' Attaches fixture fd5 to the body of toothbrush
      box2->CreateFixture(&fd6); //!<'box2->CreateFixture(fd6)' Attaches fixture fd6 to the body of toothbrush

      //!The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-22, 20); //!<'b2Vec2 worldAnchorOnBody1(-22, 20)' Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(-5, 10); //!<'b2Vec2 worldAnchorOnBody2(-5, 10)' Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-22, 25); //!<'b2Vec2 worldAnchorGround1(-22, 25)' Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-5, 25); //!<'b2Vec2 worldAnchorGround2(-5, 25)' Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; //!<'float32 ratio = 1.0f' Defined ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);/*!<'myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio)' Initializes myjoint with 2 bodies, 2 ground anchors, 2 local anchors*/
      m_world->CreateJoint(myjoint); //!<'m_world->CreateJoint(myjoint)' Creates the pulley
    }
    
  
    

    //!The revolving horizontal platform
    {
      b2PolygonShape shape; //!<'b2PolygonShape shape' Declares a polygon shape for the platform
      shape.SetAsBox(5.2f, 0.2f); /*!<'shape.SetAsBox(5.2f, 0.2f)' creates a box with width 10.4f and height 0.4f */
      b2BodyDef bd; //!<'b2BodyDef bd' Declares a body definition
      bd.position.Set(1.f, 12.5f); //!<'bd.position.Set(1.f, 12.5f) Sets the position of the body definition
      bd.type = b2_dynamicBody; //!<'bd.type = b2_dynamicBody' Sets the type as dynamic
      b2Body* body = m_world->CreateBody(&bd); //!<'b2Body* body = m_world->CreateBody(&bd)' Creates a body with bd as the body definition
      b2FixtureDef *fd = new b2FixtureDef; /*!<'b2FixtureDef *fd = new b2FixtureDef' Create a fixture fd and subsequently define the density and shape*/
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd); //!<'body->CreateFixture(fd)' Attaches the fixture to the body

	 //!The hinge
	 //!< It is defined in the simlar manner as the hinge for the right revolving part with appropriate coordinates
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(1.f, 14.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);
	 
	 //!<And now we create an anchor between the hinge and the platform
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //!The heavy sphere on the platform
    //!<It is defined in the same manner as previously defined balls exception being density and coordinates of the ball
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.3;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(1.f, 16.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }

	
    //!The see-saw system at the bottom
    {
      //!The triangle wedge
      //!< It is defined in the similar manner as defined for the weight balance system with appropriate coordinates
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,3.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.01f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-35.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //!The plank on top of the wedge
      b2PolygonShape shape; //!<'b2PolygonShape shape' Creates a polygon shape
      shape.SetAsBox(10.0f, 0.2f); //!<'shape.SetAsBox(10.0f, 0.2f)' creates a box with width 10.4f and height 0.4f 
      b2BodyDef bd2; //!<'b2BodyDef bd2' Declares a body definition
      bd2.position.Set(-35.0f, 3.0f); //!<'bd2.position.Set(-35.0f, 3.0f)' Sets the position of the body definition
      bd2.type = b2_dynamicBody; //!<'bd2.type = b2_dynamicBody' Sets the body to dynamic type
      b2Body* body = m_world->CreateBody(&bd2); /*!<'b2Body* body = m_world->CreateBody(&bd2)' Creates a pointer to the body with bd2 as the body definition*/
      b2FixtureDef *fd2 = new b2FixtureDef; /*!<'b2FixtureDef *fd2 = new b2FixtureDef' Declares a fixture and subsequently initialize the density, shape, density*/
      fd2->density = 0.8f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      b2FixtureDef fds; //!<'b2FixtureDef fds' Creates another fixture
      b2PolygonShape shapes; //!<'b2PolygonShape shapes' Declares a polygon shape for the barrier
      shapes.SetAsBox(0.2f,1.f,b2Vec2(10.0f,1.0f),0.0); /*!<'shapes.SetAsBox(0.2f,1.f,b2Vec2(10.0f,1.0f),0.0)' creates a box with width 0.4f and height 2.f, centre of the box as (10.0f,1.0f) and 0 radian rotation of the box*/
      fds.shape=&shapes;
      body->CreateFixture(fd2); //!<'body->CreateFixture(fd2)' Attaches fixture fd2 to the body
      body->CreateFixture(&fds); //!<'body->CreateFixture(&fds)' Attaches fixture fds to the body

      b2RevoluteJointDef jd;//!<'b2RevoluteJointDef jd' the joint around which the plank rotates
      b2Vec2 anchor; //!<'b2Vec2 anchor' Creates a verctor representing the position of the anchor in the subsequent lines
      anchor.Set(-35.0f, 3.0f);
      jd.Initialize(sbody, body, anchor); //!<'jd.Initialize(sbody, body, anchor)' Initializes the joint with the 2 bodies and the anchor
      m_world->CreateJoint(&jd); //!<'m_world->CreateJoint(&jd)' Creates the anchor

      //!The light box on the right side of the see-saw
      //!<Box is created in the similar manner as are the shelves with modified breaadth and appropriate coordinates
      b2PolygonShape shape2; 
      shape2.SetAsBox(1.0f, 1.0f); 
      b2BodyDef bd3; 
      bd3.position.Set(-41.0f, 3.5f); 
      bd3.type = b2_dynamicBody; 
      b2Body* body3 = m_world->CreateBody(&bd3); 
      b2FixtureDef *fd3 = new b2FixtureDef; 
      fd3->density = 1.f; 
      fd3->shape = new b2PolygonShape; 
      fd3->shape = &shape2; 
      body3->CreateFixture(fd3);
      
      //!Box restricting the motion of plank
      //!<This box is placed below the left hand side plank to restrict the motion
      b2PolygonShape shape3; 
      shape3.SetAsBox(1.0f, 1.5f); 
      b2BodyDef bd4; 
      bd4.position.Set(-43.0f, 0.5f); 
      bd4.type = b2_dynamicBody; 
      b2Body* body4 = m_world->CreateBody(&bd4); 
      b2FixtureDef *fd4 = new b2FixtureDef; 
      fd4->density = 0.01f; 
      fd4->shape = new b2PolygonShape; 
      fd4->shape = &shape3; 
      body4->CreateFixture(fd4);
      
      
    }

    //!The box containing water
    /*!<Box is created in the similar fashion as above with water being defined as a polygon shaped body with the body definition's bullet setting set to false */
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-0.7f,3.0f),b2Vec2(-0.7f,0.f));
      b2EdgeShape shape1;
      shape1.Set(b2Vec2(-9.f,3.f),b2Vec2(-9.f,0.f));
      b2BodyDef bd;
      b2Body* f = m_world->CreateBody(&bd);
      f->CreateFixture(&shape,0.0f);
      f->CreateFixture(&shape1,0.0f);

      b2PolygonShape water;
      water.SetAsBox(4.1f,1.f);
      b2BodyDef bd2;
      bd2.type=b2_dynamicBody;
      bd2.bullet=false;
      bd2.position.Set(-4.8,1.f);
      b2Body* wat = m_world->CreateBody(&bd2);
      wat->CreateFixture(&water,0.0f);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
