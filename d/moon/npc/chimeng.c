// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//change.c
inherit NPC;
#include <ansi.h>
inherit F_MASTER;
string ask_sanshou();

void create()
{
       set_name("�����ɹ�",({"chi meng","dream", "fairy"}));
       set("long",
"�����Խ�����ɹ�Ҳ�����ܽ���֮л��������Ե�߶�֮��\n");
       set("title", "�Խ����");
       set("gender", "Ů��");
       set("age", 18);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "�ɹ�");
       set("per", 30);
   set("int", 30);
       set("max_kee", 1000);
       set("max_gin", 1000);
       set("max_sen", 1000);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 500);
       set("mana", 500);
       set("mana_factor", 40);
       set("combat_exp", 1000000);

        set("eff_dx", 100000);
        set("nkgain", 300);

       set_skill("literate", 90);
       set_skill("parry", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 100);
       set_skill("force", 120);
       set_skill("whip", 180);
       set_skill("unarmed", 80);
       set_skill("spells", 120);
       set_skill("baihua-zhang", 120);
        set_skill("moonshentong",140);
        set_skill("jueqingbian", 180);
        set_skill("moonforce", 120);
        set_skill("moondance", 100);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("whip", "jueqingbian");
        map_skill("parry", "jueqingbian");
        map_skill("dodge", "moondance");
        set("inquiry",([
      "����������": (: ask_sanshou :),
      ]));


create_family("�¹�", 2, "����");
setup();

       // carry_object("/d/obj/book/lovebook");
        carry_object("/d/obj/cloth/luoyi")->wear();
   carry_object("/d/obj/weapon/whip/jueqingwhip")->wield();
}
string ask_sanshou()
{
    object me=this_player();

    if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
    if(me->query("faith")<500)
       return ("��Ա������˶��ٹ��ף�����������������֣�");
    if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
//    if(me->query("family/master_id") != "chi meng")
//     return ("�㲻���ҵĵ���,������\n");
    if(me->query("JQB_known"))
      return ("�㲻���Ѿ�֪����ô���ѵ�����ϷŪ�ҵģ�");
    command("pat "+me->query("id"));
    me->set("JQB_known",1);
    return ("�㸽��������������������������...");
}
void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="Ů��")){
           command("shake");
           command("say �����¹�ֻ��Ůͽ����λ" +
   RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
           return ;
        }
//if (random(this_player()->query_kar()) < 3 || this_player()->query("mark/moon_chimeng")){
//     this_player()->set("mark/moon_chimeng", 1);
//     command("shake");
//     command("say ������Ե����������߾Ͱɡ�\n");
//     return ;
//   }
        else{
   command("pat "+ob->query("id"));
        command("say ��Ȼ" + RANK_D->query_respect(ob) +
"������Ե���Ҿ��������ˡ�\n");
        command("recruit " + ob->query("id") );
        return ;
}
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
     ob->set("title", HIM"�����ɹ��״�����"NOR);
}
