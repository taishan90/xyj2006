#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("ѩɽ����", ({"baipao", "pao", "cloth"}));
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һ��˿�ư��ۣ���������һֻ�������ѵĴ�����\n");
		set("material", "cloth");
		set("unit", "��");
		set("value", 600);
		set("armor_prop/armor", 4);
		set("armor_prop/personality", 1);
	}
	setup();
}


