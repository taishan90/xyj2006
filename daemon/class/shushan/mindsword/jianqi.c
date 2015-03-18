#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, sword;
        string msg;

if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("������������ɽ�ɲ���֮��Ҳ��\n");


        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon = me->query_temp("weapon")) 
           || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽����������á�����������\n");

//        if (weapon->query("unique"))
//                return notify_fail("������֮�����Ƿ���֮����ʹ�á�������û��ʲô���ã�\n");

        if (uptime() - me->query_temp("last_pf_time") < 5 ) 
                return notify_fail("���ʹ�꡸��������Ŀǰ��Ѫ��ӿ���޷��ٴ����ã�\n");
        
 if( (int)me->query_skill("mindsword", 1) < 100 ||
//    if( (int)me->query_skill("mindsword", 1) < 900 ||

           (int)me->query_skill("sword", 1) < 100 ||
            (int)me->query_str() <=25 )
  return notify_fail("����Ϊ����������δ�����򡸽�������\n");
// return notify_fail("�����ر�,�ȴ�������\n");

        if( me->query_skill("zixia-shengong", 1) < 100 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�������\n");

        if( me->query_skill_mapped("force") != "zixia-shengong")
                return notify_fail("�����õ��ڹ��롸�������ķ���㣣�\n");
        if (me->query_skill_mapped("sword") != "mindsword" ||
            me->query_skill_mapped("parry") != "mindsword")
                return notify_fail("�������������һ������еľ��С�\n");                                                                                 
      
        if( me->query("max_force") <= 1000 )
                return notify_fail("���������Ϊ���㣬����������ʩչ����������\n");

        if( me->query("force") <= 300 )
                return notify_fail("�����������������������ʩչ����������\n");

        
        message_vision(HIM"\nͻȻ$N�����������֣�Ǳ��������"+weapon->name()+HIM"һ������һ��ʹ�ý����ݺᣬ��Ȼ����ɽ�ȡ���������֮�ˣ��޲����죡\n\n" NOR, me);
        
        if (random(me->query("combat_exp")) > target->query("combat_exp")/3 )
        {
                me->start_busy(1);

                damage = (int)me->query_skill("mindsword", 1) + (int)me->query_skill("force",1);
                damage = damage/2 + random(damage/2);
                target->receive_damage("kee", damage);
                target->start_busy(2+random(3));
                me->add("force", -100);
                msg = HIR"$n����$N������ǧ���Ľ���������֪����мܣ�\n"NOR;
        }
        else
        {
                me->start_busy(random(3));
                msg = HIR"$n����Ϊ����Ц��:����֮��,Ҳ�����������ԣ�\n"NOR;
        }
        message_vision(msg, me, target);
        me->set_temp("last_pf_time",uptime());
        return 1;
}

