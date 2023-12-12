using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayerLife : MonoBehaviour
{
    float reloadDelay = 2.0f;

    bool playerLifeStatus = false;

    [SerializeField] AudioSource playerDead;
    [SerializeField] AudioSource levelReload;

    private void Update()
    {
        if(transform.position.y < -5.0f)
        {
            GameTerminate();
            Debug.Log("Fell Down");
            Invoke(nameof(GameReload), reloadDelay);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("Enemy"))
        {
            GameTerminate();
            Invoke(nameof(GameReload), reloadDelay);
        }
    }

    void GameTerminate()
    {
        playerLifeStatus = false;
        GetComponent<MeshRenderer>().enabled = false;
        GetComponent<Rigidbody>().isKinematic = true;
        GetComponent<playerMovement>().enabled = false;
        playerDead.Play();
    }

    void GameReload()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        levelReload.Play();
    }
}
