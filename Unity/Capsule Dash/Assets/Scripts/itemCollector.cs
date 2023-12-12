using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class itemCollector : MonoBehaviour
{
    int playerScore = 0;

    [SerializeField] Text scoreText;
    [SerializeField] AudioSource collectionSound;

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Coin"))
        {
            Destroy(other.gameObject);
            collectionSound.Play();
            playerScore++;
            scoreText.text = "Score: " + playerScore.ToString();
        }
    }
}
