//模板方法  
//在固定的步骤确定的情况下，通过堕胎机制在多个子类中对每个步骤的细节进行差异化实现，这就是木板方法模式能够达到的效果。
//模板方法模式：行为型模式

//步骤：
//一个具体实现范例的逐步重构
//引入模板方法（Template Method）模式
//
//


//(1)一个具体实现范例的逐步重构
//A公司有一个小游戏项目组--开发单机闯关打斗类游戏（类似接机打拳游戏）。
//一个游戏项目组最少需要三名单人不同角色的员工组成：游戏策划、游戏程序、游戏美术。

//游戏策划需求：游戏主角是个战士（攻击力不强，生命值多，抗揍），主角通过不断往前走来闯关，遇到敌人就进行攻击
		//敌人也会反击，敌人在近距离时也会主动攻击
		//主角：生命值--1000（为0，时主角死亡，游戏结束），魔法值--0（暂时用不上，保留），攻击力--200（打敌人一下
		//技能“燃烧”--使用该技能，使附近所有敌人损失500技能，但是自身也会损失300点生命值。


//增加法师作为主角（攻击力很强，生命值比较少，不抗揍）
//生命值--800（为0，时主角死亡，游戏结束），魔法值--200（暂时用不上，保留），攻击力--300（打敌人一下
//技能“燃烧”--使用该技能，使附近所有敌人损失650技能，但是自身损失100点魔法值。

//将要增加牧师 作为主角  
//每一个主角都有一个叫做 燃烧 的主角     每个主角释放    燃烧技能时效果各不相同。   有两点不变：1、对自身产生影响  2、对敌人产生影响

/*战士和法师释放   燃烧   技能表现是不同的，这种不同的表现主要是通过F_Warrior和F_Mage子类中的effect_enemy和effect_self虚函数来体现出不同*/


//（2）引入模板方法（Template Method）模式
//软件开发中需求变化频繁，开发人员尝试寻找变化点，把变化部分和稳定部分分开，在变化的地方应用设计模式
//学习设计模式不难，难的是在何时何地使用
//设计模式中往往会把  成员函数  说成是算法
//晚绑定    代码执行时才知道具体要执行哪个虚函数
//早绑定	编译时就能确定执行哪个子类



/*模板方法模式的定义(实现意图)：定义了一个操作中的算法的骨架（稳定部分），而将一些步骤延迟到子类中去实现（父类中定义虚函数，
	子类中实现，从而达到在整体稳定的情况下能够产生一些变化的目的*/
//模板方法模式也被认为导致了一种反向控制结构--这种结构被称为好莱坞法则--不要来调用我，我会去调用你。

/*设计模式的经典总结：设计模式的作用就是在变化和稳定中间寻找隔离点，分离稳定和变化，从而管理变化。*/




#include <iostream>


using namespace std;

namespace _nmsp1
{
	//定义一个“战士”类
	class Warrior
	{
	public:
		//构造函数
		Warrior(int life, int magic, int attack) :m_life(life), m_magic(magic), m_attack(attack)
		{

		}
		//....一些成员函数,暂时与设计模式练习无关 不重要，不深究

	public:
		void JN_Burn()//技能   燃烧
		{
			cout << "让所有敌人损失500生命值，相关逻辑代码 略……"<<endl;
			cout << "主角失去300生命值" << endl;
			m_life -= 300;
			cout << "播放技能“燃烧”的技能特效给玩家看" << endl;
		}
	private:
		//角色属性
		int m_life;
		int m_magic;
		int m_attack;
	};
}

namespace _nmsp2
{
	class Fighter
	{
	public:
		Fighter(int life, int magic, int attack) :m_life(life), m_magic(magic), m_attack(attack)
		{
		}
		virtual ~Fighter() {}



		//对主角自身会产生迎新，对敌人会产生影响
		//分析：对敌人产生影响，有函数effect_enemy.对主角产生影响，函数effect_self.
		//播放技能play_effect函数

	
		void JN_Burn()
		{
			effect_enemy();
			effect_self();
			play_effect();
		}
	protected:
		int m_life;
		int m_magic;
		int m_attack;

	private:
		virtual void effect_enemy() {}//函数体为空，表示啥也不做，如果要求子类中重新实现该虚函数，则可以将该函数写成纯虚函数
		virtual void effect_self(){}
		void play_effect()
		{
			cout << "播放技能 “燃烧”特效" << endl;//所有主角的技能特效相同，不用写成虚函数并在子类实现。
		}
		
	};
	//---------------------
	//‘战士类’   父类是Fighter
	class F_Warrior:public Fighter
	{
	public:
		F_Warrior(int life, int magic, int attack) :Fighter(life,magic,attack)
		{
		}
		

	private:
		//对敌人产生影响
		virtual void effect_enemy() 
		{
			cout << "战士主角让所有敌人失去500生命值，" << endl;

		}
		//对自身产生的影响
		virtual void effect_self()
		{
			cout << "战士主角-自身损失300生命值" << endl;
			m_life -= 300;
		}
	};
	//---------------------------
	//‘法师’类，父类为FIghter
	class F_Mage :public Fighter
	{
	public:
		F_Mage(int life, int magic, int attack) :Fighter(life, magic, attack)
		{
		}

	private:
		//对敌人产生影响
		virtual void effect_enemy()
		{
			cout << "法师主角让所有敌人失去650生命值，" << endl;

		}
		//对自身产生的影响
		virtual void effect_self()
		{
			cout << "法师主角-自身损失100魔法值" << endl;
			m_magic -= 100;
		}
	};
}
int main()
{
	//_nmsp1::Warrior mroleobj(1000, 0, 200);//创建主角
	//mroleobj.JN_Burn();//释放燃烧技能


	_nmsp2::Fighter* prole_war = new _nmsp2::F_Warrior(1000, 0, 200);//创建战士主角，注意这里是父类指针指向子类对象以利用多态特性。
	prole_war->JN_Burn();//战士主角释放‘燃烧’
	cout << "-------------------------" << endl;//分割线，以便更醒目提示
	_nmsp2::Fighter* prole_mag = new _nmsp2::F_Mage(800, 200, 300);//创建法师主角，
	prole_mag->JN_Burn();//法师主角释放“燃烧”技能

	//释放资源
	delete prole_mag;
	delete prole_war;

	//早绑定
	/*_nmsp2::F_Warrior role_war(1000, 0, 200);
	role_war.JN_Burn();*/

	return 0;
}