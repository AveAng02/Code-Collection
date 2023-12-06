using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerMovement : MonoBehaviour
{
    [SerializeField]
    private float move = 5;

    [SerializeField]
    private float jump = 4;

    private float moveX;

    private Rigidbody2D myBody;

    private SpriteRenderer charSprite;

    private Animator anim;
    private string WALK_ANIMATION = "walk";

    private bool onGround;
    private string GROUND_TAG = "ground";

    private void Awake()
    {
        myBody = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();

        charSprite = GetComponent<SpriteRenderer>();
    }

    // Start is called before the first frame update
    void Start()
    {
        onGround = true;
    }

    // Update is called once per frame
    void Update()
    {
        playerMoveKeyboard();
        AnimatePlayer();

        PlayerJump();
    }

    void playerMoveKeyboard()
    {
        moveX = Input.GetAxisRaw("Horizontal");

        transform.position += new Vector3(moveX, 0f, 0f) * Time.deltaTime * move;
    }

    void AnimatePlayer()
    {
        Debug.Log("Move X is " + moveX);

        // moving to right
        if (moveX > 0)
        {
            anim.SetBool(WALK_ANIMATION, true);
            charSprite.flipX = false;
        }
        // move left
        else if (moveX < 0)
        {
            anim.SetBool(WALK_ANIMATION, true);
            charSprite.flipX = true;
        }
        else
        {
            anim.SetBool(WALK_ANIMATION, false);
        }
    }

    void PlayerJump()
    {
        if(Input.GetButtonUp("Jump") && onGround)
        {
            Debug.Log("Jump pressed");

            onGround = false;
            myBody.AddForce(new Vector2(0f, jump), ForceMode2D.Impulse);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.CompareTag(GROUND_TAG))
        {
            onGround = true;
        }
    }
}
