package Test;

import java.util.Set;

import org.hibernate.Session;
import org.hibernate.Transaction;

import Util.HibernateUtil;
import entity.Grade;
import entity.Student;

public class test {
     
	public static void add()
	{
		Grade g = new Grade();
		g.setName("������༶");
		g.setNumber(50);
		
		Student s1 = new Student();
		s1.setName("С��");
		s1.setSex("��");
		
		Student s2 = new Student();
		s2.setName("С��");
		s2.setSex("Ů");
		
		
		g.getStudent().add(s1);
		g.getStudent().add(s2);
		
		Session session = HibernateUtil.getSession();
		Transaction ts = session.beginTransaction();
		session.save(g);
		session.save(s1);
		session.save(s2);
		ts.commit();
		HibernateUtil.closeSession(session);
	}
	
	  
		public static void add_1()
		{
			Grade g = new Grade();
			g.setName("���ù���༶");
			g.setNumber(30);
			
			Student s1 = new Student();
			s1.setName("С��");
			s1.setSex("��");
			
			Student s2 = new Student();
			s2.setName("С��");
			s2.setSex("Ů");
			
			
			g.getStudent().add(s1);
			g.getStudent().add(s2);
			
			Session session = HibernateUtil.getSession();
			Transaction ts = session.beginTransaction();
			session.save(g);
			session.save(s1);
			session.save(s2);
			ts.commit();
			HibernateUtil.closeSession(session);
		}
		
		public static void find()
		{
			Session session = HibernateUtil.getSession();
			Grade g = (Grade)session.get(Grade.class, 1);
			System.out.println(g);
			
			Set<Student> student = g.getStudent();
			for(Student s:student)
				System.out.println(s);
		}
		
		public static void update()
		{
			Grade g = new Grade();
			g.setName("��Ϣ����רҵ");
			g.setNumber(60);
			
			Session session = HibernateUtil.getSession();
			Student stu = (Student) session.get(Student.class, 1);
			g.getStudent().add(stu);
			session.save(g);
			
			Transaction ts = session.beginTransaction();
			ts.commit();
			HibernateUtil.closeSession(session);
		}

		public static void Delete()
		{		
			Session session = HibernateUtil.getSession();
			Student stu = (Student) session.get(Student.class, 2);
			session.delete(stu);
			
			Transaction ts = session.beginTransaction();
			ts.commit();
			HibernateUtil.closeSession(session);
		}
		
	public static void main(String[] args) {

		//add();add_1();
	//find();
		//update();
		Delete();
	}
}
