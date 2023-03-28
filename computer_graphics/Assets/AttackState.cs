using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackState : StateMachineBehaviour
{

    Enemy enemy;

    // ���� ����
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        enemy = animator.GetComponent<Enemy>();
    }

    // ���� ����
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        Debug.Log("�������� ��ġ�� �����ϰ� �ֽ��ϴ�!");
        //PlayerStat.instance.Hit(5);
        PlayerStat.instance.Hit(animator.GetComponent<EnemyStat>().atk);
    }

    // ���� ����
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        enemy.atkDelay = enemy.atkCooltime;
    }
}
