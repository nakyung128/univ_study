using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeManager : MonoBehaviour
{
    public SpriteRenderer white;
    public SpriteRenderer black;
    // 빠르기를 함수 호출할 때 달리 할 수 있도록 애니메이터 사용 안 함
    private Color color; // 이미지의 투명도 조절

    private WaitForSeconds waitTime = new WaitForSeconds(0.01f);

    // 파라미터 안 넣었을 때 기본 속도 0.02f
    public void FadeOut(float _speed = 0.02f)
    {
        StartCoroutine(FadeOutCoroutine(_speed));
    }

    IEnumerator FadeOutCoroutine(float _speed)
    {
        color = black.color;

        while (color.a < 1f)
        {
            color.a += _speed;
            black.color = color;
            yield return waitTime; // 대기
        }
    }

    // 반짝임을 담당하는 함수
    /*public void Flash(float _speed = 0.1f)
    {
        StartCoroutine(FlashCoroutine(_speed));
    }

    IEnumerator FlashCoroutine(float _speed)
    {
        color = white.color;

        while (color.a < 1f)
        {
            color.a += _speed;
            white.color = color;
            yield return waitTime;
        }
        while (color.a < 0)
        {
            color.a -= _speed;
            white.color = color;
            yield return waitTime;
        }
    }*/

    public void FadeIn(float _speed = 0.02f)
    {
        StartCoroutine(FadeInCoroutine(_speed));
    }

    IEnumerator FadeInCoroutine(float _speed)
    {
        color = black.color;
        
        // 알파값이 0이 되면 검은색이 사라졌다는 것이니 페이드인
        while (color.a > 0f)
        {
            color.a -= _speed;
            black.color = color;
            yield return waitTime; // 대기
        }
    }

    public void FlashOut(float _speed = 0.02f)
    {
        StartCoroutine(FlashOutCoroutine(_speed));
    }

    IEnumerator FlashOutCoroutine(float _speed)
    {
        color = white.color;

        while (color.a < 1f)
        {
            color.a += _speed;
            white.color = color;
            yield return waitTime; // 대기
        }
    }

    public void FlashIn(float _speed = 0.02f)
    {
        StartCoroutine(FlashInCoroutine(_speed));
    }

    IEnumerator FlashInCoroutine(float _speed)
    {
        color = white.color;

        while (color.a > 0f)
        {
            color.a -= _speed;
            white.color = color;
            yield return waitTime; // 대기
        }
    }
}
