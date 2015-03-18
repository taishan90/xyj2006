// passwd.c by canoe 

inherit F_CLEAN_UP;

int main(object me, string arg)
{
   object ob;

   if( me != this_player(1) ) return 0;

   ob = me->query_temp("link_ob");
   if( !ob ) return 0;
   while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");
   if(ob->query("super_password"))
      {
        write("Ϊ�˰�ȫ����������������Ĺ������룺");
        input_to("get_old_super_password",1,ob);
      }      
   else
   {
   write("����û�й������룬���μ�2006�������趨һ��(suppwd)��\n");
   write("Ϊ�˰�ȫ���������������ԭ�������룺");
   input_to("get_old_pass", 1, ob);
   }
   return 1;
}

private void get_old_super_password(string pass, object ob)
{
   string old_pass;

   write("\n");
   old_pass = ob->query("super_password");
   if( crypt(pass, old_pass)!=old_pass ) {
     write("�����������\n");
     "adm/daemons/monitord"->report_system_object_msg(ob,"��ͼ�ô���Ĺ����������޸ĵ�½���롣");
     return;
   }
   write("��ϲ����ͨ�������ݼ���\n");
   write("Ϊ�˰�ȫ���������������ԭ�������룺");
   input_to("get_old_pass", 1, ob);
   
}
private void get_old_pass(string pass, object ob)
{
   string old_pass;

   write("\n");
   old_pass = ob->query("password");
   if( crypt(pass, old_pass)!=old_pass ) {
     write("�������\n");
          MONITOR_D->report_passwd_error(ob,"change passwd,wrong in passwd");
     return;
   }
   write("�������µ����룺");
   input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
   write("\n");
        if( strlen(pass)<5 ) {
                write("��������Ҫ������ַ���ɣ��������������룺");
                input_to("get_new_pass", 1, ob);
                return;
        }
   write("\n��������һ���µ����룺");
   input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
   write("\n");
   if( crypt(pass, new_pass)!=new_pass ) {
     write("�Բ�������������벢����ͬ������ʹ��ԭ�������롣\n");
     return;
   }
   seteuid(getuid());
   if( !ob->set("password", new_pass) ) {
     write("������ʧ�ܣ�\n");
     return;
   }

   ob->save();
   write("�������ɹ���\n");
}

int help(object me)
{
   write(@HELP
ָ���ʽ : passwd
 
���ָ������޸�����������롣
 
HELP
    );
    return 1;
}