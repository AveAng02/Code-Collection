using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaypointFollower : MonoBehaviour
{
    [SerializeField] GameObject[] wayPoints;
    int currentPoint = 0;

    [SerializeField] float speed = 1.0f;


    // Update is called once per frame
    void Update()
    {
        if (Vector3.Distance(transform.position, wayPoints[currentPoint].transform.position) < 0.1f)
        {
            currentPoint++;
            currentPoint %= wayPoints.Length;
        }

        transform.position = Vector3.MoveTowards(transform.position, wayPoints[currentPoint].transform.position, speed * Time.deltaTime);
    }
}
