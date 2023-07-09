from django.shortcuts import render, redirect
from django.http import HttpResponse
from .models import *
from .forms import *
# For user forms
from django.contrib.auth.forms import UserCreationForm
# For user authentication
from django.contrib.auth import authenticate, login, logout
# For messages
from django.contrib import messages
# For not opening index before login
from django.contrib.auth.decorators import login_required, permission_required
# For decorators
from .decorators import *
# For getting user data
from django.contrib.auth import get_user_model

# Create your views here.
@login_required(login_url='login')
# @permission_required('tasks.add_task')
def index(request):
    tasks = Task.objects.all()
    form = TaskForm()
    if request.method=='POST':
        form = TaskForm(request.POST)
        if form.is_valid():
            form.save()
        return redirect("/")  # it will redirect and reload the entire page and set all the tasks by objects.all() function
    context = {'tasks': tasks, 'form': form} # same as params
    return render(request, 'tasks/index.html', context)

@allowed_users(allowed_roles=['admin'])
def showUsers(request):
    User = get_user_model()
    users = User.objects.all()
    context = {'users': users}
    return render(request, 'tasks/show.html', context)

@login_required(login_url='login')
def updateTask(request, pk):
    task = Task.objects.get(id=pk)
    form = TaskForm(instance=task)
    if request.method=='POST':
        form = TaskForm(request.POST, instance=task)
        if form.is_valid():
            form.save()
        return redirect('/')
    context = {'form': form, 'Id': task.id}
    return render(request, 'tasks/update.html', context)

@login_required(login_url='login')
def delete(request, pk):
    obj = Task.objects.get(id=pk)
    if request.method=='POST':
        obj.delete()
        return redirect('/')
    context = {'obj': obj}
    return render(request, 'tasks/delete.html', context)


@unauthenticated_user
def loginUser(request):
    if request.method=='POST':
        username = request.POST.get('username')
        password = request.POST.get('password')
        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return redirect('main')
        else:
            messages.info(request, 'Username or Password incorrect')         
    return render(request, 'tasks/login.html')

def logoutUser(request):
    logout(request)
    return redirect('login')

@unauthenticated_user
def register(request):
    # if request.user.is_authenticated:
    #     return redirect('main')               This can be efficiently done using decorators!
    form = CreateUserForm()
    if request.method=='POST':
        form = CreateUserForm(request.POST)
        if form.is_valid():
            form.save()
            user = form.cleaned_data.get('username')
            messages.success(request, 'Account was created for '+user)
            return redirect('login')

    context = {'form': form}
    return render(request, 'tasks/register.html', context)