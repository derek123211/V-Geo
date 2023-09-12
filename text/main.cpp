#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include<fstream>
#include "time.h"

#include <SFML/Graphics.hpp>

#include "include/vector2.h"
#include "include/triangle.h"
#include "include/delaunay.h"
#include "include/voronoisquare.h"


float RandomFloat(float a, float b) {
    const float random = ((float) rand()) / (float) RAND_MAX;
    const float diff = b - a;
    const float r = random * diff;
    return a + r;
}

int main(int argc, char * argv[])
{
    clock_t start_time=clock();
    int numberPoints = 0;
    int numberusers=0;
    /*if (argc==1)
    {
        numberPoints = (int) roundf(RandomFloat(4, numberPoints));
    }
    else if (argc>1)
    {
        numberPoints = atoi(argv[1]);
    }*/
    //srand (time(NULL));


    std::vector<Vector2<float> > edgenotes;
    std::ifstream in("C:/Users/csn/Desktop/text/Edgenode.txt");
    while(1)
    {
        float x1=0;
        float y1=0;
        in>>x1>>y1;
        if(x1!=0||y1!=0)
        {
            edgenotes.push_back(Vector2<float>(x1, y1));
            numberPoints++;
        }else{break;}

    }
    in.close();

    std::vector<Vector2<float> > users;
    std::ifstream on("C:/Users/csn/Desktop/text/user.txt");
    while(1)
    {
        float x1=0;
        float y1=0;
        in>>x1>>y1;
        if(x1!=0||y1!=0)
        {
             users.push_back(Vector2<float>(x1, y1));
            numberusers++;
        }else{break;}

    }



//    for(int i = 0; i < numberPoints; ++i) {
//        points.push_back(Vector2<float>(RandomFloat(0, 800), RandomFloat(0, 600)));
//    }


    Delaunay<float> triangulation;
    const std::vector<Triangle<float> > triangles = triangulation.triangulate(edgenotes);
    std::cout << triangles.size() << " triangles generated\n";

    const std::vector<Edge<float> > edges = triangulation.getEdges();


//    std::cout << " ========= "<<"\n"<<std::endl;



    std::vector<Edge<float> > voronoiedge;//维诺边
    std::ofstream outfile;
    outfile.open("C:/Users/csn/Desktop/text/voronoi.txt");
    for(const auto &e : edges)
        {   int cnt=0;
            int number=0;
            for(int i=0;i<=triangles.size();i++)
            {
                if(e==triangles[i].e1||e==triangles[i].e2||e==triangles[i].e3)
                {
                    cnt++;
                    if(cnt==2)
                    {
                        outfile<<triangles[number].oc.x<<"   "<<triangles[number].oc.y<<"      "<<triangles[i].oc.x<<"   "<<triangles[i].oc.y<<"\n"<<std::endl;
                        voronoiedge.push_back(Edge<float>(triangles[number].oc, triangles[i].oc));
                    }
                    number=i;
                }
            }
            if(cnt==1)
                outfile<<triangles[number].oc.x<<"   "<<triangles[number].oc.y<<"\n"<<e<<"\n"<<std::endl;
                //voronoiedge.push_back(Edge<float>(triangles[number].oc, e.m));
        }
    outfile.close();
    std::vector<Vector2<float> > pointsoc;

    for(int i=0;i<=triangles.size();i++)
    {pointsoc.push_back(Vector2<float>(triangles[i].oc.x, triangles[i].oc.y));}




    sf::RenderWindow window(sf::VideoMode(800,800), "Delaunay triangulation");


    std::vector<sf::RectangleShape*> squares;
    for(const auto p : edgenotes) {
        sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(4, 4));
        c1->setPosition(p.x, p.y);
        squares.push_back(c1);
    }

    std::vector<std::array<sf::Vertex, 2> > lines;
    for(const auto &e : voronoiedge) {
        lines.push_back({{
                                 sf::Vertex(sf::Vector2f(e.p1.x + 2, e.p1.y + 2)),
                                 sf::Vertex(sf::Vector2f(e.p2.x + 2, e.p2.y + 2))
                         }});
    }

//    for(const auto &e : edges) {
//        lines.push_back({{
//                                 sf::Vertex(sf::Vector2f(e.p1.x + 2, e.p1.y + 2)),
//                                 sf::Vertex(sf::Vector2f(e.p2.x + 2, e.p2.y + 2))
//                         }});
//    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        for(const auto &s : squares) {
            window.draw(*s);
        }


        for(const auto &l : lines) {
            window.draw(l.data(), 5, sf::Lines);
        }

        window.display();
    }





    clock_t end_time=clock();
    std::cout <<(end_time-start_time)<<std::endl;
    return 0;
}
