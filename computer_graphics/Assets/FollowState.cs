using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowState : StateMachineBehaviour
{
    Transform enemyTransform;
    Enemy enemy;
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        enemy = animator.GetComponent<Enemy>();
        enemyTransform = animator.GetComponent<Transform>();
    }

    // OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
    override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if(Vector2.Distance(enemy.player.position, enemyTransform.position) > 400)
        {
            animator.SetBool("isBack", true);
            animator.SetBool("isFollow", false);
        }
        else if (Vector2.Distance(enemy.player.position, enemyTransform.position) > 100f)
        {
            enemyTransform.position = Vector3.MoveTowards(enemyTransform.position, enemy.player.position, Time.deltaTime * enemy.speed);
        }
        else
        {
            animator.SetBool("isBack", false);
            animator.SetBool("isFollow", false);
        }
        enemy.DirectionEnemy(enemy.player.position.x, enemyTransform.position.x);
    }

    // OnStateExit is called when a transition ends and the state machine finishes evaluating this state
    override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {

    }
}
