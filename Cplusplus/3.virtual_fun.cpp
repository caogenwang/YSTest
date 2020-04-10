#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;
//纯虚函数不对实例化，只能继承
class Shape{
public:
    Shape(){}
    virtual ~Shape(){}
    virtual double GetArea() = 0;
    virtual double GetPerim() = 0;
    virtual void Draw() = 0;
};
void Shape::Draw()
{
    cout<<"Draw shape"<<endl;
}
//必须覆盖父类的纯虚函数,都实现了父类的纯虚函数虚函数，不再是抽象类
class Circle:public Shape{
    public:
        Circle(int R):R(R){}
        virtual ~Circle(){}
        double GetArea(){ return 3.14 * R * R;}
        double GetPerim(){return 2*3.14*R;}
        void Draw();
    private:
    int R;
};
void Circle::Draw(){
    cout<<"Draw Circle"<<endl;
}

class Rectangle:public Shape{
    public:
        Rectangle(int width,int height):width(width),height(height){}
        virtual ~Rectangle(){}
        double GetArea(){return width * height;}
        double GetPerim(){return 2*width + 2*height;}
        void Draw();
    private:
        int width;
        int height;
};
void Rectangle::Draw(){
    cout<<"Draw  Rectangle"<<endl;
}

class Square:public Rectangle{
public:
    Square(int len);
    Square(int width,int height);
    virtual ~Square(){}
    void Draw();
};
Square::Square(int len):Rectangle(len,len){}
Square::Square(int width,int height):Rectangle(width,height){

}
void Square::Draw()
{
    cout<<"Draw Square"<<endl;
}

// int main()
// {
//     Shape *s = new Square(8);
//     s->Draw();
//     delete s;
//     return 0;
// }

enum COLOR {RED,BLUE,BLACK};

class Animal
{
    public:
    Animal(int);
    virtual ~Animal(){};
    virtual int GetAge() const {return age;}
    virtual void SetAge(int age) {this->age = age;}
    virtual void Sleep() const = 0;
    virtual void Eat() const = 0;
    virtual void Reproduce() const = 0;
    virtual void Move() const = 0;
    virtual void Speak() const = 0;
    private:
        int age;
};
Animal::Animal(int age):age(age)
{
    cout<<"construct"<<endl;
}

class Mannal:public Animal{
    public:
        Mannal(int age):Animal(age){
            cout<<"Mannal construct"<<endl;
        }

        virtual ~Mannal(){cout<<"Mannal delete"<<endl;}
        virtual void Reproduce() const
        {
            cout<<"Mannal Reproduce"<<endl;
        }
};

class Fish:public Animal{
    public:
        Fish(int age):Animal(age){cout<<"Fish construct"<<endl;}
        virtual ~Fish(){cout<<"Fish Delete"<<endl;}
        virtual void Sleep() const{cout<<"Fish Sleep"<<endl;};
        virtual void Eat() const {cout<<"Fish Eat"<<endl;};
        virtual void Reproduce() const {cout<<"Fish Reproduce"<<endl;};
        virtual void Move() const {cout<<"Fish Move"<<endl;};
        virtual void Speak() const {cout<<"Fish Speak"<<endl;};
};

class Horse : public Mannal{
    public:
        Horse(int age,COLOR color):Mannal(age),color(color){
            cout<<"Horse construct"<<endl;
        }
        virtual ~Horse(){cout<<"Horse delete"<<endl;}
        virtual void Sleep() const{cout<<"Horse Sleep"<<endl;};
        virtual void Speak() const {cout<<"Horse Speak"<<endl;};
        virtual COLOR getColor() const {return color;}
        virtual void Eat() const {cout<<"Horse Eat"<<endl;};
        virtual void Move() const {cout<<"Horse Move"<<endl;};
    protected:
        COLOR color;
};

class Dog : public Mannal{
    public:
        Dog(int age,COLOR color):Mannal(age),color(color){
            cout<<"Dog construct"<<endl;
        }
        virtual ~Dog(){cout<<"Dog delete"<<endl;}
        virtual void Sleep() const{cout<<"Dog Sleep"<<endl;};
        virtual void Speak() const {cout<<"Dog Speak"<<endl;};
        virtual COLOR getColor() const {return color;}
        virtual void Eat() const {cout<<"Dog Eat"<<endl;};
        virtual void Reproduce() const {cout<<"Dog Reproduce"<<endl;};
        virtual void Move() const {cout<<"Dog Move"<<endl;};
    protected:
        COLOR color;
};

int main()
{
    Animal *panimal = 0;
    panimal = new Horse(1,RED);
    panimal->Eat();
    delete panimal;
    return 0;
}