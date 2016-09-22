package open.hui.ren.initialsofhanzi;

import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;
import android.test.suitebuilder.annotation.LargeTest;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.closeSoftKeyboard;
import static android.support.test.espresso.action.ViewActions.replaceText;
import static android.support.test.espresso.assertion.ViewAssertions.matches;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;

/**
 * @author renhui
 * @date 16-9-22
 * @desc open.hui.ren.initialsofhanzi
 */

@RunWith(AndroidJUnit4.class)
@LargeTest
public class MainActivityTest {
    private String mStringToBetyped;
    private String mStringResult;

    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(
        MainActivity.class);

    @Before
    public void initValidString() {
        // Specify a valid string.
        mStringToBetyped = "你好";
        mStringResult = "NH";
    }

    @Test
    public void changeText_sameActivity() {
        // Type text and then press the button.
        onView(withId(R.id.editText))
            .perform(replaceText(mStringToBetyped), closeSoftKeyboard());
        onView(withId(R.id.btn_ok)).perform(click());

        // Check that the text was changed.
        onView(withId(R.id.editText))
            .check(matches(withText(mStringResult)));
    }

}
