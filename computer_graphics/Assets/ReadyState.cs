using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReadyState : StateMachineBehaviour
{
    Transform enemyTransform;
    Enemy enemy;

    // 상태 진입
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        enemy = animator.GetComponent<Enemy>();
        enemyTransform = animator.GetComponent<Transform>();
    }

    // 상태 진행
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if(enemy.atkDelay <= 0)
        animator.SetTrigger("Attack");

        if (Vector2.Distance(enemy.player.position, enemyTransform.position) > 100f)
        {
            animator.SetBool("isFollow", true);
        }
        enemy.DirectionEnemy(enemy.player.position.x, enemyTransform.position.x);
    }

    // 상태 종료
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {

    }
}
