using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class monsterSpawner : MonoBehaviour
{
    [SerializeField]
    private GameObject[] enemyRef;

    private GameObject spawnedMonster;

    [SerializeField]
    private Transform leftPos, rightPos;

    private int randomIndex;
    private int randomSide;

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(SpawnMonsters());
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    IEnumerator SpawnMonsters()
    {
        while(true)
        {
            yield return new WaitForSeconds(Random.Range(1, 5));

            randomIndex = Random.Range(0, enemyRef.Length);
            randomSide = Random.Range(0, 2);

            spawnedMonster = Instantiate(enemyRef[randomIndex]);

            // Left side
            if (randomSide == 0)
            {
                spawnedMonster.transform.position = leftPos.position;
                spawnedMonster.GetComponent<monsterScript>().speed = Random.Range(4, 10);
            }
            else // Right Side
            {
                spawnedMonster.transform.position = rightPos.position;
                spawnedMonster.GetComponent<monsterScript>().speed = Random.Range(4, 10);
                spawnedMonster.transform.localScale = new Vector3(-1f, 1f, 1f);
            }

        } // while
    }
}
