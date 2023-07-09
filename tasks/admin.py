from django.contrib import admin
from .models import *
# Register your models here.
admin.site.register(Task)   # this is the Task model(which you created in models.py) registration to admin 