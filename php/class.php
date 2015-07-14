<?php
/**
 * parent　只能调用父类中的公有或受保护的方法，不能调用父类中的属性
 * self 　可以调用父类中除私有类型的方法和属性外的所有数据
 */
class User{
    public $name;
    private $passwd;
    protected $email;    
    public  function __construct(){
        //print __CLASS__." \n";
        $this->name= 'User';
        $this->passwd='666';
        $this->email = 'user@163.com';
    }    
    public function show(){
        print __CLASS__."show \n";
    }    
    public function inUserClassPublic() {
        print __CLASS__.'::'.__FUNCTION__." \n";
    }    
    protected  function inUserClassProtected(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }    
    private function inUserClassPrivate(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
}

class simpleUser extends User {    
    public function __construct(){        
        //print __CLASS__." \n";
        parent::__construct();
    }
    
    public function show(){
        print $this->name."//public   ";        
        print $this->passwd."//private   ";
        print $this->email."//protected   \n";
    }
    
    public function inSimpleUserClassPublic() {
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
    
    protected function inSimpleUserClassProtected(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
    
    private function inSimpleUserClassPrivate() {
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
}

class adminUser extends simpleUser {
    protected $admin_user;
    public function __construct(){
        //print __CLASS__." \n";
        parent::__construct();
    }
    
    public function inAdminUserClassPublic(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
    
    protected function inAdminUserClassProtected(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
    
    private function inAdminUserClassPrivate(){
        print __CLASS__.'::'.__FUNCTION__." \n";
    }
}

class administrator extends adminUser {
    public function __construct(){        
        parent::__construct();
        $this->name= 'administrator';
        $this->passwd='admin';
        $this->email = 'admin@163.com';
    }
}

/**
 * 在类的实例中 只有公有属性和方法才可以通过实例化来调用
 */
$s = new administrator();
print '-------------------';
$s->show();
$s->inUserClassPublic();
print $s->name;
print $s->passwd;
//print $s->email; //cannot

//$s->inUserClassProtected();
//$s->inUserClassPrivate();


?>

