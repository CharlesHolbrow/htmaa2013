requestSerialMsg = function(e){
  self = this; // assume this is a jquery handler
  e.preventDefault();
  $.ajax({
    data:{value:self.innerHTML},
    url:'serial/',
    type:'post'
  }).done(function(data){
    console.log('.done data', data);
  }).fail(function(jqXHR, textStatus, errorThrown){
    console.log('errorThrown:', errorThrown);
    console.log('textStatus:', textStatus);
  });
};

$(function(){
  var serialLinks = $('a.serial');
  serialLinks.click(requestSerialMsg).mouseenter(requestSerialMsg);
});
