package open.hui.ren.initialsofhanzi;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import open.hui.ren.iofhan.library.JNIEntrance;

public class MainActivity extends Activity {

    @BindView(R.id.editText)
    EditText editText;
    @BindView(R.id.btn_ok)
    Button   btnOk;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
    }

    @OnClick({R.id.btn_ok})
    public void whenClick(View view){
        switch (view.getId()){
            case R.id.btn_ok:
                String s  = editText.getText().toString().trim();
                String ss = JNIEntrance.getStringInitials(s);
                editText.setText(ss);
                break;
            default:
                break;
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

}
